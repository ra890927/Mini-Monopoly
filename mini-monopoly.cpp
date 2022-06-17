#include<stdio.h>
#include<string.h>
#include<vector.h>


int main(){
	int PlayerCount=0;
	printf("How many payers?(Maxinum:4)...>");
	scanf("%d",&PlayerCount);
	if(PlayerCount<1 || PlayerCount>4){
		cout << "only for 1-4 players\n" << endl;
		return 0;
	}
	getchar();
	int CurrentPlayer=0;
	vector<string> PlayerName;
	vector<string> PlayerNameDefault = {"A-Tu","Littlee-Mei","King-Baby","Mrs.Money"};
	
	char input[20];
	for(int i=0;i<PlayerCount;++i){
		cout << "\nPlease input player 1's name(Default: "<<PlayerNameDefault[i]<<")...>" << endl;
		cin.getline( input,20 );
		if(strlen(input) == 0){
			PlayerName.push_back(PlayerNameDefault[i]);
		}
		else{
			PlayerName.push_back(input);
		}
		getchar();
	}
//vector<Player> player_list;
//cin >> player_name;
//
//Player p(player_name);
//player_list.push_back(p);


do{
	NextPlayer(CurrentPlayer);
    PrintMap();//«a§»
	PrintProfile(CurrentPlayer);
    dice = DiceRoll();
    update(CurrentPlayer,dice)//«a§»
    checkPoint(CurrentPlayer)//«a§»
    if(CheckWhos()==NULL){//¶R¦a 
		printf("%s, do you want to buy %s? (1:Yes [default] / 2:No)...>",GetName(CurrentPlayer),GetPosition(CurrentPlayer));
		scanf("%d",option);
        if(option != 2){
        	buy(CurrentPlayer);
		}
    }
    else if(CheckWhos()==CurrentPlayer){//¤É¯Å 
    	if(upgradable(CurrentPlayer)){
    		printf("%s, do you want to upgrade %s? (1:Yes [default] / 2:No)...>",GetName(CurrentPlayer),GetPosition(CurrentPlayer));	
		}
        scanf("%d",option);
        if(option != 2){
        	upgrade(CurrentPlayer);
		}
    }
    else if (MapUnit() == J){//§¤¨c 
        jail(CurrentPlayer);
    } 
    else if (CheckWhos()!=CurrentPlayer){//»@¿ú 
        fine(CurrentPlayer);

    }
	if(broken(CurrentPlayer)){
        out(CurrentPlayer);   
    }

//    §PÂ_¬O§_µ²§ô
}while(PlayerCount > 1)
} 
