struct tree{
	struct tree * left;
	struct tree * right;
	/* int dane */
};
int countleaves(struct tree * root){
	int result=0;
	if( root->left )
		result= countleaves(root->left);
	if( root->right )
		result+= countleaves(root->right);
	if( result )
		return result;
	else
		return 1;
}
int getheight(struct tree * root){
	int result=-1;
	int resultright;
	if( root->left )
		result= countleaves(root->left);
	if( root->right ){
		resultright=countleaves(root->right);
		if(resultright>result)
			result=resultright;
	}
	return result+1;
}
int diffrence=0;
int maxtwinsdiffrence(struct tree * root){
	int result=-1;
	int resultright;
	int diff=0;
	if( root->left )
		result= maxtwinsdiffrence(root->left);
	if( root->right ){
		resultright=maxtwinsdiffrence(root->right);
		if( root->left){
			diff=result-resultright;
			if(diff<0)
				diff=-diff;
			if(diff>diffrence)
				diffrence=diff;
		}
		if(resultright>result)
			result=resultright;
	}
	return result+1;
}
