#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include <treezeug/treezeug.h>
#include <treezeug/AttributeMap.h>
#include <treezeug/Node.h>


namespace zeug
{

struct TreeData;

class TREEZEUG_API Tree
{
	friend class Node;
public:
	Tree(const std::string& name);
	virtual ~Tree();

	Node* root();
	const Node* root() const;
	void setRoot(Node* node, int id = 0);

	const std::string& name() const;
	void setName(const std::string& name);

	unsigned size() const;
	int maxId() const;

	Node* getNode(int id) const;

	Node* getNodeByPath(const std::string& path, char separator = '/');

	void nodesDo(std::function<void(Node*)> action);
	void nodesDo(std::function<void(const Node*)> action) const;
	void nodesOrderedByDepthDo(std::function<void(Node*)> action);
	void nodesOrderedByDepthDo(std::function<void(const Node*)> action) const;
	void leavesDo(std::function<void(Node*)> action);
	void leavesDo(std::function<void(const Node*)> action) const;

	bool hasAttributeMap(const std::string & name) const;
	void addAttributeMap(const std::string & name, AttributeMap::Type type);

    AttributeMap::Type attributeMapType(const std::string & name) const;
	const std::vector<std::string> & attributes() const;
    void renormalizeAttributeForLeaves(const std::string& attribute);

	unsigned depth() const;

	Tree * copy() const;
	Tree * restrictTo(Node * newRoot) const;
	Tree * restrictTo(int id) const;

protected:
    std::shared_ptr<TreeData> m_data;
};

struct TreeData
{
    friend class Tree;
public:
    TreeData(const std::string& name);
    ~TreeData();

    void setRoot(Node* node, int id);

    void registerNode(Node * node, bool silent = false);
    void deregisterNode(Node * node);

    bool hasAttributeMap(const std::string & name) const;
    void setAttribute(
        const Node * node
    ,   const std::string & name
    ,   double value);

    void setAttribute(
        const Node * node
    ,   const std::string & name
    ,   const std::string & value);

    const Attribute * attribute(const Node * node, const std::string & name) const;
protected:
    std::string m_name;
    Node * m_root;

    std::unordered_map<int, Node*> m_idMap;

    int m_nextId;
    unsigned m_depth;

    std::unordered_map<std::string, AttributeMap*> m_attributeMaps;
    std::vector<std::string> m_attributes;
};

} // namespace zeug
