#ifndef BEHAVIOUR_TREE
#define BEHAVIOUR_TREE

class Node
{
public:
	virtual void addChild(std::shared_ptr<Node> newChild) { children.emplace_back(newChild); };
	virtual std::vector<std::shared_ptr<Node>> getChildren() { return children; };

protected:
	std::shared_ptr<Node> parent;
	std::vector<std::shared_ptr<Node>> children;
};

class ControlFlow : protected Node
{

};

class Selector : protected ControlFlow
{

};

class Sequencer : protected ControlFlow
{

};

class ParallelSelector : protected ControlFlow
{

};

class ParallelSequencer : protected ControlFlow
{

};

class Decorator : protected Node
{
public:
	virtual void addChild(std::shared_ptr<Node> newChild) { if (!children.size()) children.emplace_back(newChild); };
};

class Inverter : protected Decorator			// Maybe shift to scripting
{

};

class Timer : protected Decorator				// Maybe shift to scripting
{

};

class LeafNode : protected Node
{

};

class BehaviourTree
{
private:
	std::shared_ptr<ControlFlow> root;			// First node, has to be a control flow
};

#endif