#include "HierarchiMultiWay_old.h"

#include <iostream>

PrvokHierarchie HierarchiMultiWay::najdi_uzemny_celok(Type p_typUzemnehoCeloku, string p_nazov)
{
	PrvokHierarchie *child = this->root_;
	Type povodnyTyp = KRAJINA;
	while (child->getChild()->at(0).getData().getType() == p_typUzemnehoCeloku)
	{
		child = &child->getChild()->at(0);
		povodnyTyp = child->getChild()->at(0).getData().getType();
	}

	auto children = child->getChild();
	for (auto it = children->begin(); it != children->end(); ++it)
	{
		int index = std::distance(children->begin(), it);

		auto data = children->at(index).getData();
		if (data.getTitle() == p_nazov)
		{
			return children->at(index);
		}
	}
}

void HierarchiMultiWay::VypisChildren(vector<PrvokHierarchie> p_children)
{
	for (int i = 0 ; i < p_children.size() ; i++)
	{
		//cout << p_children.at(i).getChild(). << endl;
	}
}

HierarchiMultiWay::HierarchiMultiWay(PrvokHierarchie* p_root)
{
	this->root_ = p_root;
}

PrvokHierarchie* HierarchiMultiWay::getRoot()
{
	//cout << root_ << endl;
	return this->root_;
}
