class HingedDoor{
public int numSwings(int &initialAngle,int &reduction){
int cnt=0;
int ang=5; 
while(ang<initialAngle){
ang*=reduction;
cnt++;
}
return cnt;
}
};
int main(){
  return 0;
}
