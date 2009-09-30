template <class keyT,class valT>
struct splayNode{
	typedef splayNode<keyT,valT>likeme;
	keyT key;
	valT val;

};
template <class keyT,class valT>
struct splayTree{
	typedef splayTree<keyT,valT>treeT;
	typedef splayNode<keyT,valT>nodeT;
	nodeT * root;


	splayTree():root(0){}
	void assign(keyT & key,valT & val){
	}
	splayNode * find_node(keyT & key){

	}
	valT * find(keyT & key){
		splayNode * n=find_node(key);
		if(n)
			return &n->val;
		else
			return 0;
	}
};
