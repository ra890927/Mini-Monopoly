#include"stdio.h"
#include"string.h"

int main(){
	int player_count=0;
	printf("How many payers?(Maxinum:4)...>");
	scanf("%d",&player_count);
	if(player_count<1 || player_count>4){
		printf("only for 1-4 players\n");
		return 0;
	}
	getchar();
	int current_player=0;
	
	char player1_name[20];
	printf("\nPlease input player 1's name(Default: A-Tu)...>");
	scanf("%[^\n]",player1_name);
	if(strlen(player1_name) == 0){
		strcpy(player1_name,"A-Tu");
	}
	getchar();
	printf("%s\n",player1_name);
	printf("strlen = %d\n",strlen(player1_name));
	
	char player2_name[20];
	printf("Please input player 2's name(Default: Little-Mei)...>");
	scanf("%[^\n]",player2_name);
	if(strlen(player2_name) == 0){
		strcpy(player2_name,"jfir");
	}
	getchar();
	printf("%s\n",player2_name);
	printf("strlen = %d\n",strlen(player2_name));
	
	char player3_name[20];
	printf("Please input player 3's name(Default: King-Baby)...>");
	scanf("%[^\n]",player3_name);
	if(strlen(player3_name) == 0){
		strcpy(player3_name,"King-Baby");
	}
	getchar();
	printf("%s",player3_name);
	
	char player4_name[20];
	printf("Please input player 4's name(Default: Mrs.Money)...>");
	scanf("%[^\n]",player4_name);
	if(strlen(player4_name) == 0){
		strcpy(player4_name,"Mrs.Money");
	}
	getchar();
	printf("%s",player4_name);

//vector<Player> player_list;
//cin >> player_name;
//
//Player p(player_name);
//player_list.apush_back(p);


do{
    print_map();//«a§»
	print_profile();
    dice = dice_roll();
    update(current_player,dice)//«a§»
    check_point(player)//«a§»
    if(check_whos()==NULL){//¶R¦a 
		printf("%s, do you want to buy %s? (1:Yes [default] / 2:No)...>",get_name(current_player),get_position(current_player));
		scanf("%d",option);
        if(option != 2){
        	buy(current_player);
		}
    }
    else if(check_whos()==current_player){//¤É¯Å 
    	if(upgradable(current_player)){
    		printf("%s, do you want to upgrade %s? (1:Yes [default] / 2:No)...>",get_name(current_player),get_position(current_player));	
		}
        scanf("%d",option);
        if(option != 2){
        	upgrade(current_player);
		}
    }
    else if (MapUnit() == J){//§¤¨c 
        jail(current_player);
    } 
    else if (check_whos()!=current_player){//»@¿ú 
        fine(current_player);
        
    }
	if(broken(current_player)){
        out(current_player);   
    }
    
//    §PÂ_¬O§_µ²§ô
}while(player_count > 1)
} 
