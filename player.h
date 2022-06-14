#ifndef PLAYER__
#define PLAYER__

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

class Player{
	public:
		Player( int id , string name ){
			id_ = id ;
			money_ = 25000 ;
			position_ = 0 ;
			name_ = name ;
		//	owned_city_ 
		}
		
		void lose_money( int m ){
			money_ -= m ;
		}
		
		void gain_money( int m ){
			money_ += m ;
		}
		
		void add_city( int city_id ){
			owned_city_.push_back( city_id ) ;
		}
		
		void move( int dice_point ){
			position_ += dice_point ;
		}
		
		bool isbankrup() const {
			return ( money_ < 0 )?true:false ;
		}
		
		int get_id() const {
			return id_ ;
		}
		
		int get_money() const {
			return money_ ;
		}
		
		string get_name() const {
			return name_ ;
		}
		
		vector<int> get_owned_city() const {
			return owned_city_ ;
		}
	
	private:
		int id_ ;
		int money_ ;
		int position_ ;
		string name_ ;
		vector<int> owned_city_ ; // 擁有的city 
};

#endif