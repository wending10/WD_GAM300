#ifndef ECS_
#define ECS_

#include <cstdint>
#include <new>
#include <string>
#include <cstddef>
#include <vector>
#include <algorithm> 
#include <functional>
#include <unordered_map>
#include <iostream>
#include <chrono>

// reference: https://indiegamedev.net/2020/05/19/an-entity-component-system-with-data-locality-in-cpp/

// TYPEDEFS ===========================================================================================
typedef std::uint32_t                   IDType;
typedef IDType                          EntityID;
typedef IDType                          ComponentTypeID;
typedef std::vector<ComponentTypeID>    ArchetypeID;
typedef unsigned char*                  ComponentData;

// CONSTS =============================================================================================
const IDType                            NULLENTITY = 0;

// FORWARD DECLARATIONS ===============================================================================
class                                   ECS;
class                                   Entity;

// TYPE ID GENERATOR CLASS ============================================================================
// Class to generate IDs
template<typename T>
class TypeIdGenerator
{
public:
    template<typename U>
    static const IDType getNewID();

private:
    inline static IDType                    mCount = 0;
};

// ARCHETYPE CLASS ====================================================================================
// Class to differentiate the archetypes and store the entity information of each archetype
class Archetype
{
public:
    // ArchetypeID - sparse vector of ComponentIDs 
    // example: if components are in the order Physics, Collision, Texture
    // an entity that has Physics and Texture will have the ArchetypeID of 101
    ArchetypeID                         type;

    // vector of pointers to the start of the data of each component
    // (data is stored by component, then entity ID, not by entityID first)
    std::vector<ComponentData>          componentData;

    // vector of sizes of each component data
    std::vector<std::size_t>            componentDataSize;

    // vector of entity IDs that are under this archetype
    // entities with Physics, and entities with Physics and Collision are under 2 different archetypes
    std::vector<EntityID>               entityIds;
};


//base class helps us by allowing child class to store any type of component
//by having a non-template base-class we can store any templated version of the child class using a pointer and polymorphism.

// SYSTEM BASE CLASS ==================================================================================
class SystemBase
{
public:
    virtual ~SystemBase() {}
    virtual ArchetypeID getKey() const = 0;
    virtual void doAction(const float elapsedTime, Archetype* archetype) = 0;
};

// SYSTEM CLASS =======================================================================================
template<class... Cs>
class System : public SystemBase
{
public:
    virtual ArchetypeID getKey() const override;

    typedef std::function<void(const float, const std::vector<EntityID>&, Cs*...)> Func;

    void action(Func func);

    //System(ECS& ecs, const std::uint8_t& layer);

protected:
    template<std::size_t Index1, typename T, typename... Ts>
    std::enable_if_t<Index1 == sizeof...(Cs)>
        doAction(const float elapsedMilliseconds,
            const ArchetypeID& archeTypeIds,
            const std::vector<EntityID>& entityIDs,
            T& t,
            Ts... ts);

    template<std::size_t Index1, typename T, typename... Ts>
    std::enable_if_t<Index1 != sizeof...(Cs)>
        doAction(const float elapsedMilliseconds,
            const ArchetypeID& archeTypeIds,
            const std::vector<EntityID>& entityIDs,
            T& t,
            Ts... ts);

    virtual void doAction(const float elapsedMilliseconds,
        Archetype* archetype) override;

    ECS& mECS;
    Func mFunc;
    bool mFuncSet;

public:
    System(ECS& theECS, const std::uint8_t& layer) : mECS(theECS), mFuncSet(false)
    {
        mECS.registerSystem(layer, this);
    }
};

class ComponentBase
{
public:
    virtual ~ComponentBase() {}
    virtual void constructData(unsigned char* data) const = 0;
    virtual void moveData(unsigned char* source, unsigned char* destination) const = 0;
    virtual void destroyData(unsigned char* data) const = 0;
    virtual std::string getName() const = 0;
    virtual void setName(std::string name) = 0;
    virtual std::size_t getSize() const = 0;
};

//templated child class
template<class C>
class Component : public ComponentBase 
{

public:
    virtual void destroyData(unsigned char* data) const override;

    virtual void moveData(unsigned char* source, unsigned char* destination) const override;

    virtual void constructData(unsigned char* data) const override;

    virtual std::size_t getSize() const override;

    virtual std::string getName() const override;

    static ComponentTypeID getTypeID();

    virtual void setName(std::string name) override;

private:
    std::string componentName;
};

class ECS 
{
private:
    typedef std::unordered_map<ComponentTypeID, ComponentBase*> ComponentTypeIDBaseMap;

    //track which entity is which archetype
    struct Record 
    {
        Archetype* archetype;
        std::size_t index;
    };

    typedef std::unordered_map<EntityID, Record> EntityArchetypeMap;


    //array of all archetypes
    typedef std::vector<Archetype*> ArchetypesArray;


    // iterate over systems to provide a way to order system calls
    typedef std::unordered_map<std::uint8_t, std::vector<SystemBase*>>
        SystemsArrayMap;

public:

    ECS();
    ~ECS();

    EntityID getNewID();

    int getSystemCount();

    template<class C>
    void registerComponent(std::string name);

    //template<class C>
    //bool IsComponentRegistered();

    void registerSystem(const std::uint8_t& layer, SystemBase* system);

    void registerEntity(const EntityID entityId);

    void runSystems(const std::uint8_t& layer, const float elapsedMilliseconds);

    Archetype* getArchetype(const ArchetypeID& id);

    template<typename C, typename... Args>
    C* addComponent(const EntityID& entityId, Args&&... args);

    template<typename C>
    void removeComponent(const EntityID& entityId);

    template<typename C>
    C* getComponent(const EntityID& entityId);
   
    template<typename C>
    void ecsGetEntitiesWith(std::vector<EntityID>& entitiesList);


    //template<class C>
  //  bool HasComponent(const EntityID& entityId);

    void removeEntity(const EntityID& entityId);

    void removeAllEntities();

    //template<class... Cs>
   // std::vector<EntityID> GetEntitiesWith();
    void setIDCounter(int counter);

    std::vector<std::string> getAllRegisteredComponents();
    std::vector<std::string> getEntityComponents(const EntityID& entityId);
    
    std::vector<EntityID> getEntities();
    //std::vector<std::string> getEntityNames();
    //std::string* getEntityName(const EntityID& entityId);

    //change back to priv 
private:

    int systemCount = 0;

    EntityArchetypeMap mEntityArchetypeMap;

    ArchetypesArray mArchetypes;

    EntityID mEntityIdCounter;

    SystemsArrayMap mSystems;

    ComponentTypeIDBaseMap mComponentMap;
};

extern ECS ecs;

//------------------------------------------------------------------------------------------------------

//wrapper for entity ID
class Entity 
{
public:

    explicit Entity(ECS& ecs = ecs, std::string name = "nil");

    template<typename C, typename... Args>
    C* add(Args&&... args);

    template<typename C>
    C* add(C&& c);

    EntityID getID() const;


private:
    EntityID mID;
    ECS& mECS;
};

#include "ecs.hpp"

#endif //ECS_
