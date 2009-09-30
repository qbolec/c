class T{
private:
	int x;
public:
	void haha(T * other){
		other->x+=x;
	}
};
int main(){
	T a,b;
	a.haha(&b);
	return 0;
}
