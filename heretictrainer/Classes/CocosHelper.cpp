#include"CocosHelper.h"

Node* seekNodeByName(Node* root, const std::string& name)
{
	//dfs过程，找寻符合名字的node
	if (!root)
	{
		return nullptr;
	}
	//log(root->getName().c_str());
	if (root->getName() == name)
	{
		return root;
	}
	const auto& arrayRootChildren = root->getChildren();
	ssize_t length = arrayRootChildren.size();
	for (ssize_t i = 0; i < length; i++)
	{
		Node* child = dynamic_cast<Node*>(arrayRootChildren.at(i));
		if (child)
		{
			Node* res = seekNodeByName(child, name);
			if (res != nullptr)
			{
				return res;
			}
		}
	}
	return nullptr;
}