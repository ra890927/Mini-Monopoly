#include""
#include""

int main(){
	printf("How many payers?(Maxinum:4)...>");
	scanf("%d",&player);
	if(���a�ƶq<1 || ���a�ƶq>4){
		printf("only for 1-4 players\n");
		reuturn 0;
	}
vector<Player> player_list;
cin >> player_name;

Player p(player_name);
player_list.apush_back(p);


do{
    �L�X�a��()//�a��
    ���a���l
    �ˬd�L���I���y(player)//�a��
    �ק缾�a��m(player,dice)//�a��
    if(�ˬd�a�O�֪�()==NULL){
        �Ror not 
    }
    else if(�ˬd�a�O�֪�()==�ۤv){
        �ˬd�O�_�i�H�ɯ�()
        �ɯ�or not 
    }
    else if (MapUnit() == J){
        �@�^�X�����(player)
    } 
    else if (�ˬd�a�O�֪�()!=�ۤv){
        �@��(player) 
        if(�}��()){
            �X��(player) //�a��
            // ��������g�a() �åB�g�a�����k1 for �Τl
        }
    }
    
    �P�_�O�_����
}while(�Ѿl���a�H�� > 1)
