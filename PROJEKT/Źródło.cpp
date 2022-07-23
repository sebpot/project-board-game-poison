#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
#define MAX 135 //maksymalna ilosc kart

typedef struct deck_of_cards {
	int value;
	char* color;
}deck_of_cards;

typedef struct hand {
	int value;
	char* color;
}hand;

typedef struct amount {
	int deck1;
	int deck2;
	int deck3;
	int deck4;
	int deck5;
	int deck6;
	int hand1;
	int hand2;
	int hand3;
	int hand4;
	int hand5;
	int hand6;
	int pile1;
	int pile2;
	int pile3;
	int pile4;
	int pile5;
	int pile6;
}amount;

typedef struct colors{
	int blue;
	int red;
	int violet;
	int yellow;
	int white;
	int black;
}colors;

typedef struct check {
	int player1;
	int player2;
	int player3;
	int player4;
	int player5;
	int player6;
}check;

typedef struct piles {
	int colors1;
	int colors2;
	int colors3;
	int colors4;
	int colors5;
	int colors6;
	int explosion1;
	int explosion2;
	int explosion3;
	int explosion4;
	int explosion5;
	int explosion6;
}piles;

typedef struct piles_sums {
	int first;
	int second;
	int third;
	int fourth;
	int fifth;
	int sixth;
}piles_sums;

deck_of_cards* create_green(deck_of_cards* deck, int g, int gv){
	for (int i = 0; i < g; i++)
	{
		deck[i].value = gv;
		deck[i].color = (char*)malloc(10*sizeof(char));
		strcpy(deck[i].color,"green");
	}
	return deck;
}

deck_of_cards* create_deck(deck_of_cards* deck, char color[10], int o, int g, int tab[MAX]){
	for (int i = 0; i < o; i++)
	{
		deck[i+g].value = tab[i];
		deck[i+g].color = (char*)malloc(10*sizeof(char));
		strcpy(deck[i+g].color,color);
	}
	return deck;
}

hand* create_hand_deck_pile()
{
	hand* hand0 = NULL;
	hand0 = (hand*)malloc(MAX * sizeof(hand));
	if (hand0 == NULL) exit(1);
	for (int i = 0; i < MAX; i++) {
		hand0[i].color = (char*)malloc(10 * sizeof(char));
	}
	return hand0;
}

deck_of_cards* create_new_deck()
{
	deck_of_cards* deck = NULL;
	deck = (deck_of_cards*)malloc(MAX * sizeof(deck_of_cards));
	if (deck == NULL) exit(1);
	for (int i = 0; i < MAX; i++) {
		deck[i].color = (char*)malloc(10 * sizeof(char));
	}
	return deck;
}

hand* add_card(hand* current_hand, int current_card, deck_of_cards* deck, int card_on_hand){
	current_hand[card_on_hand].value = deck[current_card].value;
	strcpy(current_hand[card_on_hand].color, deck[current_card].color);
	return current_hand;
}

int number(char line[]) {
	int i = 0;
	while (line[i] != NULL) {
		if (line[i] >= '1' && line[i] <= '9')
			return int(line[i] - '0');
		i++;
	}
	return -1;
}

int digit(char line[], int index) {
	if (line[index] >= '1' && line[index] <= '9') return 1;//znalezlismy pierwsza karte
	if (line[index] == '\n') return -1;//bialy znak
	else return 0;//znak
}

int find_first_card(char line[], int index) {
	int x = digit(line, index);
	while (x == 0) {
		index++;
		x = digit(line, index);
	}
	return index;
}

hand* fill_hand_or_deck_or_pile(hand* hand0, char line[],int *n) {
	char only_cards[500];
	int l = find_first_card(line, 1);//podajemy drugi index by ominac numer gracza
	strcpy(only_cards, line + l);//podstawiamy same karty
	only_cards[strlen(only_cards) - 1] = ' ';//nowy koniec linii
	char* line_element;
	line_element = strtok(only_cards, " ");//dzielenie linii tekstu na pojedyncze elementy
	while (line_element != NULL) {
		if (strcmp(line_element, "\n")) {
			if (atoi(line_element) != 0)
				hand0[*n].value = atoi(line_element);
			else {
				strcpy(hand0[*n].color, line_element);
				(*n)++;
			}
		}
		line_element = strtok(NULL, " ");
	}
	return hand0;
}

void print_player(hand* current_hand, int amount_of_hand,hand* current_deck,int amount_of_deck, int player)
{
	FILE* file;
	file = fopen("state_of_game.txt", "a");
	cout << player << " player hand cards: ";
	fprintf(file, "%d player hand cards: ", player);
	for (int i = 0; i < amount_of_hand; i++) {
		cout << current_hand[i].value << " " << current_hand[i].color << " ";
		fprintf(file, "%d %s ", current_hand[i].value, current_hand[i].color);
	}
	cout << endl;
	fprintf(file, "\n");
	cout << player << " player deck cards: ";
	fprintf(file, "%d player deck cards: ", player);
	for (int i = 0; i < amount_of_deck; i++) {
		cout << current_deck[i].value << " " << current_deck[i].color << " ";
		fprintf(file, "%d %s ", current_deck[i].value, current_deck[i].color);
	}
	cout << endl;
	fprintf(file, "\n");
	fclose(file);
}

void print_pile(hand* current_pile, int amount_of_pile, int this_pile) {
	FILE* file;
	file = fopen("state_of_game.txt", "a");
	cout << this_pile << " pile cards: ";
	fprintf(file, "%d pile cards: ", this_pile);
	for (int i = 0; i < amount_of_pile; i++) {
		cout << current_pile[i].value << " " << current_pile[i].color << " ";
		fprintf(file, "%d %s ", current_pile[i].value, current_pile[i].color);
	}
	cout << endl;
	fprintf(file, "\n");
	fclose(file);
}

void print_deck(deck_of_cards* deck, int s)
{
	FILE* file;
	file = fopen("deck.txt", "w");
	for (int i = 0; i < s; i++) {
		cout << deck[i].value << " " << deck[i].color << " ";
		fprintf(file, "%d %s ", deck[i].value, deck[i].color);
	}
	fprintf(file, "\n");
	fclose(file);
	cout << endl;
}

void print_players_cards(int player, int x, int y) {
	cout << player << " player has " << x << " cards on hand" << endl;
	cout << player << " player has " << y << " cards in front of him" << endl;
}

void print_piles(int k, int n) {
	cout << "there are " << n << " cards on " << k << " pile" << endl;
}

deck_of_cards* fill_deck(deck_of_cards* deck, hand* cards, int n, int* s) {
	for (int i = 0; i < n; i++) {
		deck[*s].value = cards[i].value;
		strcpy(deck[*s].color, cards[i].color);
		(*s)++;
	}
	return deck;
}

int find_one_green_card(deck_of_cards* deck, int s) {
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "green") == 0) return deck[i].value;
	}
	return 0;
}

int check_green_cards(deck_of_cards* deck, int gv, int s) {
	int g = 0;
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "green") == 0) {
			if (deck[i].value == gv) g++;
			else return 0;
		}
	}
	return g;
}

void check_number_of_colors(deck_of_cards* deck,colors *colors_of_cards, int s) {
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "blue") == 0) colors_of_cards->blue++;
		if (strcmp(deck[i].color, "red") == 0) colors_of_cards->red++;
		if (strcmp(deck[i].color, "violet") == 0) colors_of_cards->violet++;
		if (strcmp(deck[i].color, "yellow") == 0) colors_of_cards->yellow++;
		if (strcmp(deck[i].color, "white") == 0) colors_of_cards->white++;
		if (strcmp(deck[i].color, "black") == 0) colors_of_cards->black++;
	}
}

colors count_colors(colors player,hand* deck0, int n) {
	for (int i = 0; i < n; i++) {
		if (strcmp(deck0[i].color, "blue") == 0) player.blue++;
		if (strcmp(deck0[i].color, "red") == 0) player.red++;
		if (strcmp(deck0[i].color, "violet") == 0) player.violet++;
		if (strcmp(deck0[i].color, "yellow") == 0) player.yellow++;
		if (strcmp(deck0[i].color, "white") == 0) player.white++;
		if (strcmp(deck0[i].color, "black") == 0) player.black++;
	}
	return player;
}

void number_correct(int n) {
	cout << "The number cards of all colors is equal: " << n << endl;
}

void number_wrong(int k,colors colors_of_cards) {
	cout << "At least two colors with a different number of cards were found:" << endl;
	cout << "blue cards are " << colors_of_cards.blue << endl;
	cout << "red cards are " << colors_of_cards.red << endl;
	if (k > 2) cout << "violet cards are " << colors_of_cards.violet << endl;
	if (k > 3) cout << "yellow cards are " << colors_of_cards.yellow << endl;
	if (k > 4) cout << "white cards are " << colors_of_cards.white << endl;
	if (k > 5) cout << "black cards are " << colors_of_cards.black << endl;
}

deck_of_cards* zero_greens(deck_of_cards* deck, int* g, int s) {
	*g = 0;
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "green") == 0) {
			(*g)++;
			deck[i].value = 0;
		}
	}
	return deck;
}

deck_of_cards* sort(deck_of_cards* deck, int s) {
	deck_of_cards temp;
	for (int i = 0; i < s - 1; i++) {
		for (int j = 0; j < s - i - 1; j++) {
			if (deck[j].value > deck[j + 1].value) {
				temp = deck[j];
				deck[j] = deck[j + 1];
				deck[j + 1] = temp;
			}
		}
	}
	return deck;
}

int check_values(deck_of_cards* deck, int s, int k, int g) {
	int x = 0,y=0;
	for (int i = g; i < s-1; i++) {
		y++;
		if (deck[i].value == deck[i + 1].value) x++;
		else x = 0;
		if (y==k-1) {
			if (x == k - 1) {
				x = 0;
				i++; 
				y = 0;
			}
			else return 0;
		}
		
	}
	return 1;
}

void print_same_values(deck_of_cards* deck, int s) {
	cout << "The values of cards of all colors are identical:" << endl;
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "blue") == 0) {
			cout << deck[i].value << " ";
		}
	}
	cout << endl;
}

void print_different_values(deck_of_cards* deck, int k, int s) {
	cout << "The values of cards of all colors are not identical:" << endl;
	cout << "blue cards values: ";
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "blue") == 0) {
			cout << deck[i].value << " ";
		}
	}
	cout << endl;
	cout << "red cards values: ";
	for (int i = 0; i < s; i++) {
		if (strcmp(deck[i].color, "red") == 0) {
			cout << deck[i].value << " ";
		}
	}
	cout << endl;
	if (k > 2) {
		cout << "violet cards values: ";
		for (int i = 0; i < s; i++) {
			if (strcmp(deck[i].color, "violet") == 0) {
				cout << deck[i].value << " ";
			}
		}
		cout << endl;
	}
	if (k > 3) {
		cout << "yellow cards values: ";
		for (int i = 0; i < s; i++) {
			if (strcmp(deck[i].color, "yellow") == 0) {
				cout << deck[i].value << " ";
			}
		}
		cout << endl;
	}
	if (k > 4) {
		cout << "white cards values: ";
		for (int i = 0; i < s; i++) {
			if (strcmp(deck[i].color, "white") == 0) {
				cout << deck[i].value << " ";
			}
		}
		cout << endl;
	}
	if (k > 5) {
		cout << "black cards values: ";
		for (int i = 0; i < s; i++) {
			if (strcmp(deck[i].color, "black") == 0) {
				cout << deck[i].value << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int check_threshold(char line[]) {
	char* line_element;
	line_element = strtok(line, " ");//dzielenie linii tekstu na pojedyncze elementy
	while (line_element != NULL) {
		if (strcmp(line_element, "\n")) {
			if (atoi(line_element) != 0) return atoi(line_element);
		}
		line_element = strtok(NULL, " ");
	}
	return 0;
}

check check_deck(check check_cards, int s, int n) {
	int x = s / n;
	int y = s-(x * n);
	check_cards.player1 = x;
	check_cards.player2 = x;
	if (n > 2) check_cards.player3 = x;
	if (n > 3) check_cards.player4 = x;
	if (n > 4) check_cards.player5 = x;
	if (n > 5) check_cards.player6 = x;
	for (int i = 1; i < y+1; i++) {
		switch (i) {
			case 1:
				check_cards.player1++;
				break;
			case 2:
				check_cards.player2++;
				break;
			case 3:
				check_cards.player3++;
				break;
			case 4:
				check_cards.player4++;
				break;
			case 5:
				check_cards.player5++;
				break;
			case 6:
				check_cards.player6++;
				break;
		}
	}
	return check_cards;
}

check check_decks(check check_cards, int decks, int n) {
	int x = 1;
	for (int i = 0; i < decks ; i++) {
		if (x > n)x = 1;
		switch (x) {
			case 1:
				check_cards.player1--;
				break;
			case 2:
				check_cards.player2--;
				break;
			case 3:
				check_cards.player3--;
				break;
			case 4:
				check_cards.player4--;
				break;
			case 5:
				check_cards.player5--;
				break;
			case 6:
				check_cards.player6--;
				break;
		}
		x++;
	}
	return check_cards;
}

check check_piles(check check_cards, int piles, int n, int a, int k) {
	a = a - 1;
	for (int i = 0; i < piles; i++) {
		if (a == 0) a = n;
		switch (a) {
			case 1:
				check_cards.player1--;
				break;
			case 2:
				check_cards.player2--;
				break;
			case 3:
				check_cards.player3--;
				break;
			case 4:
				check_cards.player4--;
				break;
			case 5:
				check_cards.player5--;
				break;
			case 6:
				check_cards.player6--;
				break;
		}
		a--;
	}
	return check_cards;
}

int check_pile_color(int n, hand* pile0) {
	int x = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(pile0[x].color, "green") == 0) x++;
		else break;
	}
	if (x == n) return 0;
	for (int i = x; i < n - 1 ; i++) {
		if (strcmp(pile0[i+1].color, "green") != 0) {
			if (strcmp(pile0[x].color, pile0[i + 1].color) != 0) return 1;
		}
	}
	return 0;
}

piles check_pile_colors(piles check_pile, amount amount_of_cards, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6) {
	check_pile.colors1 = check_pile_color(amount_of_cards.pile1, pile1);
	check_pile.colors2 = check_pile_color(amount_of_cards.pile2, pile2);
	check_pile.colors3 = check_pile_color(amount_of_cards.pile3, pile3);
	check_pile.colors4 = check_pile_color(amount_of_cards.pile4, pile4);
	check_pile.colors5 = check_pile_color(amount_of_cards.pile5, pile5);
	check_pile.colors6 = check_pile_color(amount_of_cards.pile6, pile6);
	return check_pile;
}

int check_one_pile_explosion(int n, hand* pile0, int e) {
	int S = 0;
	for (int i = 0; i < n; i++) {
		S = S + pile0[i].value;
	}
	if (S > e) return 1;
	return 0;
}

piles check_pile_explosion(piles check_pile, amount amount_of_cards, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, int e) {
	check_pile.explosion1 = check_one_pile_explosion(amount_of_cards.pile1, pile1, e);
	check_pile.explosion2 = check_one_pile_explosion(amount_of_cards.pile2, pile2, e);
	check_pile.explosion3 = check_one_pile_explosion(amount_of_cards.pile3, pile3, e);
	check_pile.explosion4 = check_one_pile_explosion(amount_of_cards.pile4, pile4, e);
	check_pile.explosion5 = check_one_pile_explosion(amount_of_cards.pile5, pile5, e);
	check_pile.explosion6 = check_one_pile_explosion(amount_of_cards.pile6, pile6, e);
	return check_pile;
}

void print_bad_pile_colors(piles check_pile) {
	if (check_pile.colors1 == 1) cout << "Two different colors were found on the 1 pile" << endl;
	if (check_pile.colors2 == 1) cout << "Two different colors were found on the 2 pile" << endl;
	if (check_pile.colors3 == 1) cout << "Two different colors were found on the 3 pile" << endl;
	if (check_pile.colors4 == 1) cout << "Two different colors were found on the 4 pile" << endl;
	if (check_pile.colors5 == 1) cout << "Two different colors were found on the 5 pile" << endl;
	if (check_pile.colors6 == 1) cout << "Two different colors were found on the 6 pile" << endl;
}

void print_bad_pile_explosion(piles check_pile) {
	if (check_pile.explosion1 == 1) cout << "Pile number 1 should explode earlier" << endl;
	if (check_pile.explosion2 == 1) cout << "Pile number 2 should explode earlier" << endl;
	if (check_pile.explosion3 == 1) cout << "Pile number 3 should explode earlier" << endl;
	if (check_pile.explosion4 == 1) cout << "Pile number 4 should explode earlier" << endl;
	if (check_pile.explosion5 == 1) cout << "Pile number 5 should explode earlier" << endl;
	if (check_pile.explosion6 == 1) cout << "Pile number 6 should explode earlier" << endl;
}

int check_if_pile_has_color(hand hand0, int k, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6,amount amount_of_cards) {
	if (k > 0) {
		for (int i = 0; i < amount_of_cards.pile1; i++) {
			if (strcmp(hand0.color, pile1[i].color) == 0) return 1;
		}
	}
	if (k > 1) {
		for (int i = 0; i < amount_of_cards.pile2; i++) {
			if (strcmp(hand0.color, pile2[i].color) == 0) return 2;
		}
	}
	if (k > 2) {
		for (int i = 0; i < amount_of_cards.pile3; i++) {
			if (strcmp(hand0.color, pile3[i].color) == 0) return 3;
		}
	}
	if (k > 3) {
		for (int i = 0; i < amount_of_cards.pile4; i++) {
			if (strcmp(hand0.color, pile4[i].color) == 0) return 4;
		}
	}
	if (k > 4) {
		for (int i = 0; i < amount_of_cards.pile5; i++) {
			if (strcmp(hand0.color, pile5[i].color) == 0) return 5;
		}
	}
	if (k > 5) {
		for (int i = 0; i < amount_of_cards.pile6; i++) {
			if (strcmp(hand0.color, pile6[i].color) == 0) return 6;
		}
	}
	return 0;
}

int check_first_free_pile(int k, amount amount_of_cards) {
	if (amount_of_cards.pile1 == 0) return 1;
	if (amount_of_cards.pile2 == 0) return 2;
	if (k > 2 && amount_of_cards.pile3 == 0) return 3;
	if (k > 3 && amount_of_cards.pile3 == 0) return 4;
	if (k > 4 && amount_of_cards.pile3 == 0) return 5;
	if (k > 5 && amount_of_cards.pile3 == 0) return 6;
	return 0;
}

int check_first_green_pile(int k, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, amount amount_of_cards) {
	int x = 0;
	if (k > 0) {
		for (int i = 0; i < amount_of_cards.pile1; i++) {
			if (strcmp(pile1[i].color, "green") == 0) x++;
		}
	}
	if (x == amount_of_cards.pile1 && amount_of_cards.pile1 != 0) return 1;
	x = 0;
	if (k > 1) {
		for (int i = 0; i < amount_of_cards.pile2; i++) {
			if (strcmp(pile2[i].color, "green") == 0) x++;
		}
	}
	if (x == amount_of_cards.pile2 && amount_of_cards.pile2 != 0) return 2;
	x = 0;
	if (k > 2) {
		for (int i = 0; i < amount_of_cards.pile3; i++) {
			if (strcmp(pile3[i].color, "green") == 0) x++;
		}
	}
	if (x == amount_of_cards.pile3 && amount_of_cards.pile3 != 0) return 3;
	x = 0;
	if (k > 3) {
		for (int i = 0; i < amount_of_cards.pile4; i++) {
			if (strcmp(pile4[i].color, "green") == 0) x++;
		}
	}
	if (x == amount_of_cards.pile4 && amount_of_cards.pile4 != 0) return 4;
	x = 0;
	if (k > 4) {
		for (int i = 0; i < amount_of_cards.pile5; i++) {
			if (strcmp(pile5[i].color, "green") == 0) x++;
		}
	}
	if (x == amount_of_cards.pile5 && amount_of_cards.pile5 != 0) return 5;
	x = 0;
	if (k > 5) {
		for (int i = 0; i < amount_of_cards.pile6; i++) {
			if (strcmp(pile6[i].color, "green") == 0) x++;
		}
	}
	if (x == amount_of_cards.pile6 && amount_of_cards.pile6 != 0) return 6;
	return -1;
}

int find_lowest_pile_sum(int k, piles_sums pile_sum) {
	int min = 1000,m=0;
	if (pile_sum.first < min) { min = pile_sum.first; m = 1; }
	if (pile_sum.second < min) { min = pile_sum.second; m = 2; }
	if (k > 2 && pile_sum.third < min) { min = pile_sum.third; m = 3; }
	if (k > 3 && pile_sum.fourth < min) { min = pile_sum.fourth; m = 4; }
	if (k > 4 && pile_sum.fifth < min) { min = pile_sum.fifth; m = 5; }
	if (k > 5 && pile_sum.sixth < min) { min = pile_sum.sixth; m = 6; }
	return m;
}

int check_which_pile(hand hand0,int k, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6,amount amount_of_cards, piles_sums pile_sum) {
	int m;
	m = find_lowest_pile_sum(k, pile_sum);
	if (strcmp(hand0.color, "green") == 0) return m;
	m = check_if_pile_has_color(hand0, k, pile1, pile2, pile3, pile4, pile5, pile6, amount_of_cards);
	if (m != 0) return m;
	m = check_first_free_pile(k, amount_of_cards);
	if (m != 0) return m;
	m = check_first_green_pile(k, pile1, pile2, pile3, pile4, pile5, pile6, amount_of_cards);
	return m;
}

void put_card_on_pile(amount* amount_of_cards, int m, hand hand0, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6) {
	switch (m) {
		case 1:
			pile1[amount_of_cards->pile1].value = hand0.value;
			strcpy(pile1[amount_of_cards->pile1].color, hand0.color);
			amount_of_cards->pile1++;
			break;
		case 2:
			pile2[amount_of_cards->pile2].value = hand0.value;
			strcpy(pile2[amount_of_cards->pile2].color, hand0.color);
			amount_of_cards->pile2++;
			break;
		case 3:
			pile3[amount_of_cards->pile3].value = hand0.value;
			strcpy(pile3[amount_of_cards->pile3].color, hand0.color);
			amount_of_cards->pile3++;
			break;
		case 4:
			pile4[amount_of_cards->pile4].value = hand0.value;
			strcpy(pile4[amount_of_cards->pile4].color, hand0.color);
			amount_of_cards->pile4++;
			break;
		case 5:
			pile5[amount_of_cards->pile5].value = hand0.value;
			strcpy(pile5[amount_of_cards->pile5].color, hand0.color);
			amount_of_cards->pile5++;
			break;
		case 6:
			pile6[amount_of_cards->pile6].value = hand0.value;
			strcpy(pile6[amount_of_cards->pile6].color, hand0.color);
			amount_of_cards->pile6++;
			break;
		}
}

void remove_card_from_hand(int* n, hand* hand0) {
	for (int i = 0; i < *n-1; i++) {
		hand0[i].value = hand0[i+1].value;
		strcpy(hand0[i].color, hand0[i + 1].color);
	}
	hand0[*n - 1].value = 0;
	strcpy(hand0[*n - 1].color, "0");
	(*n)--;
}

int if_explosion(int e, hand* pile0, int n) {
	int S = 0;
	for (int i = 0; i < n; i++) {
		S = S + pile0[i].value;
	}
	if (S > e)return 1;
	return 0;
}

void if_explosion_clear_pile(int e, hand* deck0, int* cards_in_deck, amount* amount_of_cards, int m,hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, int *player) {
	int s;
	switch (m) {
		case 1:
			s = if_explosion(e, pile1,amount_of_cards->pile1);
			if (s == 1) {
				for (int i = 0; i < amount_of_cards->pile1; i++) {
					deck0[*cards_in_deck + i].value = pile1[i].value;
					strcpy(deck0[*cards_in_deck + i].color, pile1[i].color);
				}
				*cards_in_deck += amount_of_cards->pile1;
				amount_of_cards->pile1 = 0;
			}
			else *player = 0;
			break;
		case 2:
			s = if_explosion(e, pile2, amount_of_cards->pile2);
			if (s == 1) {
				for (int i = 0; i < amount_of_cards->pile2; i++) {
					deck0[*cards_in_deck + i].value = pile2[i].value;
					strcpy(deck0[*cards_in_deck + i].color, pile2[i].color);
				}
				*cards_in_deck += amount_of_cards->pile2;
				amount_of_cards->pile2 = 0;
			}
			else *player = 0;
			break;
		case 3:
			s = if_explosion(e, pile3, amount_of_cards->pile3);
			if (s == 1) {
				for (int i = 0; i < amount_of_cards->pile3; i++) {
					deck0[*cards_in_deck + i].value = pile3[i].value;
					strcpy(deck0[*cards_in_deck + i].color, pile3[i].color);
				}
				*cards_in_deck += amount_of_cards->pile3;
				amount_of_cards->pile3 = 0;
			}
			else *player = 0;
			break;
		case 4:
			s = if_explosion(e, pile4, amount_of_cards->pile4);
			if (s == 1) {
				for (int i = 0; i < amount_of_cards->pile4; i++) {
					deck0[*cards_in_deck + i].value = pile4[i].value;
					strcpy(deck0[*cards_in_deck + i].color, pile4[i].color);
				}
				*cards_in_deck += amount_of_cards->pile4;
				amount_of_cards->pile4 = 0;
			}
			else *player = 0;
			break;
		case 5:
			s = if_explosion(e, pile5, amount_of_cards->pile5);
			if (s == 1) {
				for (int i = 0; i < amount_of_cards->pile5; i++) {
					deck0[*cards_in_deck + i].value = pile5[i].value;
					strcpy(deck0[*cards_in_deck + i].color, pile5[i].color);
				}
				*cards_in_deck += amount_of_cards->pile5;
				amount_of_cards->pile5 = 0;
			}
			else *player = 0;
			break;
		case 6:
			s = if_explosion(e, pile6, amount_of_cards->pile6);
			if (s == 1) {
				for (int i = 0; i < amount_of_cards->pile6; i++) {
					deck0[*cards_in_deck + i].value = pile6[i].value;
					strcpy(deck0[*cards_in_deck + i].color, pile6[i].color);
				}
				*cards_in_deck += amount_of_cards->pile6;
				amount_of_cards->pile6 = 0;
			}
			else *player = 0;
			break;
	}
}

int find_most_color(int a, int b, int c, int d, int e, int f) {
	int m = a,x=0;
	if (b > m) {
		m = b;
	}
	else if (m == b) x++;
	if (c > m) {
		m = c;
		x = 0;
	}
	else if (m == c) x++;
	if (d > m) {
		m = d;
		x = 0;
	}
	else if (m == d) x++;
	if (e > m) {
		m = e;
		x = 0;
	}
	else if (m == e) x++;
	if (f > m) {
		m = f;
		x = 0;
	}
	else if (m == f) x++;
	if (x != 0) return 0;
	if (m == a) return 1;
	if (m == b) return 2;
	if (m == c) return 3;
	if (m == d) return 4;
	if (m == e) return 5;
	if (m == f) return 6;
	return -1;
}

colors count_most_colors(colors most_colors, colors player1, colors player2, colors player3, colors player4, colors player5, colors player6) {
	most_colors.blue = find_most_color(player1.blue, player2.blue, player3.blue, player4.blue, player5.blue, player6.blue);
	most_colors.red = find_most_color(player1.red, player2.red, player3.red, player4.red, player5.red, player6.red);
	most_colors.violet = find_most_color(player1.violet, player2.violet, player3.violet, player4.violet, player5.violet, player6.violet);
	most_colors.yellow = find_most_color(player1.yellow, player2.yellow, player3.yellow, player4.yellow, player5.yellow, player6.yellow);
	most_colors.white = find_most_color(player1.white, player2.white, player3.white, player4.white, player5.white, player6.white);
	most_colors.black = find_most_color(player1.black, player2.black, player3.black, player4.black, player5.black, player6.black);
	return most_colors;
}

void clear_most_color(char color[10], hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, int which_player, amount amount_of_cards) {
	switch (which_player) {
	case 1:
		for (int i = 0; i < amount_of_cards.deck1; i++) {
			if (strcmp(deck1[i].color, color) == 0) {
				deck1[i].value = 0;
			}
		}
		break;
	case 2:
		for (int i = 0; i < amount_of_cards.deck2; i++) {
			if (strcmp(deck2[i].color, color) == 0) {
				deck2[i].value = 0;
			}
		}
		break;
	case 3:
		for (int i = 0; i < amount_of_cards.deck3; i++) {
			if (strcmp(deck3[i].color, color) == 0) {
				deck3[i].value = 0;
			}
		}
		break;
	case 4:
		for (int i = 0; i < amount_of_cards.deck4; i++) {
			if (strcmp(deck4[i].color, color) == 0) {
				deck4[i].value = 0;
			}
		}
		break;
	case 5:
		for (int i = 0; i < amount_of_cards.deck5; i++) {
			if (strcmp(deck5[i].color, color) == 0) {
				deck5[i].value = 0;
			}
		}
		break;
	case 6:
		for (int i = 0; i < amount_of_cards.deck6; i++) {
			if (strcmp(deck6[i].color, color) == 0) {
				deck6[i].value = 0;
			}
		}
		break;
	}
}

void print_resistance_to_color(colors most_colors) {
	if (most_colors.blue != 0) cout << "Na kolor blue odporny jest gracz " << most_colors.blue << endl;
	if (most_colors.red != 0) cout << "Na kolor red odporny jest gracz " << most_colors.red << endl;
	if (most_colors.violet != 0) cout << "Na kolor violet odporny jest gracz " << most_colors.violet << endl;
	if (most_colors.yellow != 0) cout << "Na kolor yellow odporny jest gracz " << most_colors.yellow << endl;
	if (most_colors.white != 0) cout << "Na kolor white odporny jest gracz " << most_colors.white << endl;
	if (most_colors.black != 0) cout << "Na kolor black odporny jest gracz " << most_colors.black << endl;
}

void print_score(int player, hand* deck0, int n) {
	int S = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(deck0[i].color, "green") == 0) S += 2;
		else if (deck0[i].value != 0) S++;
	}
	cout << "Wynik gracza " << player << " = " << S << endl;
}

void print_scores(int n, hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, amount amount_of_cards) {
	print_score(1, deck1, amount_of_cards.deck1);
	print_score(2, deck2, amount_of_cards.deck2);
	if(n>2)print_score(3, deck3, amount_of_cards.deck3);
	if(n>3)print_score(4, deck4, amount_of_cards.deck4);
	if(n>4)print_score(5, deck5, amount_of_cards.deck5);
	if(n>5)print_score(6, deck6, amount_of_cards.deck6);
}

void print_state_of_the_game(int a, int n, int e, int k, hand* hand1, hand* hand2, hand* hand3, hand* hand4, hand* hand5, hand* hand6, hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5,hand* pile6,amount amount_of_cards) {
	FILE* file;
	file = fopen("state_of_game.txt", "w");
	cout << "active player = " << a << endl;//wypisuje stan gry po zagraniu
	fprintf(file, "active player = %d\n", a);
	cout << "players number = " << n << endl;
	fprintf(file, "players number = %d\n", n);
	cout << "explosion threshold = " << e << endl;
	fprintf(file, "explosion threshold = %d\n", e);
	fclose(file);
	for (int i = 0; i < n; i++){//wypisanie kart graczy
		switch (i) {
		case 0:
			print_player(hand1, amount_of_cards.hand1, deck1, amount_of_cards.deck1, 1);
			break;
		case 1:
			print_player(hand2, amount_of_cards.hand2, deck2, amount_of_cards.deck2, 2);
			break;
		case 2:
			print_player(hand3, amount_of_cards.hand3, deck3, amount_of_cards.deck3, 3);
			break;
		case 3:
			print_player(hand4, amount_of_cards.hand4, deck4, amount_of_cards.deck4, 4);
			break;
		case 4:
			print_player(hand5, amount_of_cards.hand5, deck5, amount_of_cards.deck5, 5);
			break;
		case 5:
			print_player(hand6, amount_of_cards.hand6, deck6, amount_of_cards.deck6, 6);
			break;
		}
	}
	for (int i = 0; i < k; i++) {//wypisanie kart w kociolkach
		switch (i) {
		case 0:
			print_pile(pile1, amount_of_cards.pile1, 1);
			break;
		case 1:
			print_pile(pile2, amount_of_cards.pile2, 2);
			break;
		case 2:
			print_pile(pile3, amount_of_cards.pile3, 3);
			break;
		case 3:
			print_pile(pile4, amount_of_cards.pile4, 4);
			break;
		case 4:
			print_pile(pile5, amount_of_cards.pile5, 5);
			break;
		case 5:
			print_pile(pile6, amount_of_cards.pile6, 6);
			break;
		}
	}
}

void end_of_the_game(int n, hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, amount amount_of_cards) {
	colors player1 = { 0,0,0,0,0,0 };
	colors player2 = { 0,0,0,0,0,0 };
	colors player3 = { 0,0,0,0,0,0 };
	colors player4 = { 0,0,0,0,0,0 };
	colors player5 = { 0,0,0,0,0,0 };
	colors player6 = { 0,0,0,0,0,0 };
	//zliczenie kolorow graczy
	player1 = count_colors(player1, deck1, amount_of_cards.deck1);
	player2 = count_colors(player2, deck2, amount_of_cards.deck2);
	player3 = count_colors(player3, deck3, amount_of_cards.deck3);
	player4 = count_colors(player4, deck4, amount_of_cards.deck4);
	player5 = count_colors(player5, deck5, amount_of_cards.deck5);
	player6 = count_colors(player6, deck6, amount_of_cards.deck6);
	colors most_colors = { 0,0,0,0,0,0 };
	//sprawdzenie odpornosci
	most_colors = count_most_colors(most_colors, player1, player2, player3, player4, player5, player6);
	//wyzerowanie kart na ktore gracz jest odporny
	char color[10] = "blue";
	clear_most_color(color, deck1, deck2, deck3, deck4, deck5, deck6, most_colors.blue, amount_of_cards);
	strcpy(color, "red");
	clear_most_color(color, deck1, deck2, deck3, deck4, deck5, deck6, most_colors.red, amount_of_cards);
	strcpy(color, "violet");
	clear_most_color(color, deck1, deck2, deck3, deck4, deck5, deck6, most_colors.violet, amount_of_cards);
	strcpy(color, "yellow");
	clear_most_color(color, deck1, deck2, deck3, deck4, deck5, deck6, most_colors.yellow, amount_of_cards);
	strcpy(color, "white");
	clear_most_color(color, deck1, deck2, deck3, deck4, deck5, deck6, most_colors.white, amount_of_cards);
	strcpy(color, "black");
	clear_most_color(color, deck1, deck2, deck3, deck4, deck5, deck6, most_colors.black, amount_of_cards);
	print_resistance_to_color(most_colors);//wypisuje ktory gracz jest odporny na jaki kolor
	print_scores(n, deck1, deck2, deck3, deck4, deck5, deck6, amount_of_cards);//wypisuje punkty graczy
}

int load_game(int* a, int* n, int* e, int* k, deck_of_cards* deck, hand* hand1, hand* hand2, hand* hand3, hand* hand4, hand* hand5, hand* hand6, hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, amount* amount_of_cards, colors colors_of_cards) {
	*amount_of_cards = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	colors_of_cards = { 0,0,0,0,0,0 };
	char line[500];
	FILE* file;
	file = fopen("state_of_game.txt", "r");
	fgets(line, 500, file);//wczytuje aktywnego gracza
	*a = number(line);
	fgets(line, 500, file);//wczytuje ilosc graczy
	*n = number(line);
	fgets(line, 500, file);//wczytuje limit kociolka
	*e = check_threshold(line);
	if (*n > 0) {
		fgets(line, 500, file);//karty na rece 1 gracza
		hand1 = fill_hand_or_deck_or_pile(hand1, line, &amount_of_cards->hand1);
		fgets(line, 500, file);//karty przed 1 graczem
		deck1 = fill_hand_or_deck_or_pile(deck1, line, &amount_of_cards->deck1);
	}
	if (*n > 1) {
		fgets(line, 500, file);//karty na rece 2 gracza
		hand2 = fill_hand_or_deck_or_pile(hand2, line, &amount_of_cards->hand2);
		fgets(line, 500, file);//karty przed 2 graczem
		deck2 = fill_hand_or_deck_or_pile(deck2, line, &amount_of_cards->deck2);
	}
	if (*n > 2) {
		fgets(line, 500, file);//karty na rece 3 gracza
		hand3 = fill_hand_or_deck_or_pile(hand3, line, &amount_of_cards->hand3);
		fgets(line, 500, file);//karty przed 3 graczem
		deck3 = fill_hand_or_deck_or_pile(deck3, line, &amount_of_cards->deck3);
	}
	if (*n > 3) {
		fgets(line, 500, file);//karty na rece 4 gracza
		hand4 = fill_hand_or_deck_or_pile(hand4, line, &amount_of_cards->hand4);
		fgets(line, 500, file);//karty przed 4 graczem
		deck4 = fill_hand_or_deck_or_pile(deck4, line, &amount_of_cards->deck4);
	}
	if (*n > 4) {
		fgets(line, 500, file);//karty na rece 5 gracza
		hand5 = fill_hand_or_deck_or_pile(hand5, line, &amount_of_cards->hand5);
		fgets(line, 500, file);//karty przed 5 graczem
		deck5 = fill_hand_or_deck_or_pile(deck5, line, &amount_of_cards->deck5);
	}
	if (*n > 5) {
		fgets(line, 500, file);//karty na rece 6 gracza
		hand6 = fill_hand_or_deck_or_pile(hand6, line, &amount_of_cards->hand6);
		fgets(line, 500, file);//karty przed 6 graczem
		deck6 = fill_hand_or_deck_or_pile(deck6, line, &amount_of_cards->deck6);
	}
	int s;
	s = 0;//uzupelnianie talii kartami graczy
	deck = fill_deck(deck, hand1, amount_of_cards->hand1, &s);
	deck = fill_deck(deck, deck1, amount_of_cards->deck1, &s);
	if (*n > 1) {
		deck = fill_deck(deck, hand2, amount_of_cards->hand2, &s);
		deck = fill_deck(deck, deck2, amount_of_cards->deck2, &s);
	}
	if (*n > 2) {
		deck = fill_deck(deck, hand3, amount_of_cards->hand3, &s);
		deck = fill_deck(deck, deck3, amount_of_cards->deck3, &s);
	}
	if (*n > 3) {
		deck = fill_deck(deck, hand4, amount_of_cards->hand4, &s);
		deck = fill_deck(deck, deck4, amount_of_cards->deck4, &s);
	}
	if (*n > 4) {
		deck = fill_deck(deck, hand5, amount_of_cards->hand5, &s);
		deck = fill_deck(deck, deck5, amount_of_cards->deck5, &s);
	}
	if (*n > 5) {
		deck = fill_deck(deck, hand6, amount_of_cards->hand6, &s);
		deck = fill_deck(deck, deck6, amount_of_cards->deck6, &s);
	}

	*k = 0;
	check_number_of_colors(deck, &colors_of_cards, s);
	if (colors_of_cards.blue != 0) (*k)++;
	if (colors_of_cards.red != 0) (*k)++;
	if (colors_of_cards.violet != 0) (*k)++;
	if (colors_of_cards.yellow != 0) (*k)++;
	if (colors_of_cards.white != 0) (*k)++;
	if (colors_of_cards.black != 0) (*k)++;

	if (*k > 0) {//zczytywanie kociolkow tak dlugo jak wystepuja
		fgets(line, 500, file);
		pile1 = fill_hand_or_deck_or_pile(pile1, line, &amount_of_cards->pile1);
	}
	if (*k > 1) {//zczytywanie kociolkow tak dlugo jak wystepuja
		fgets(line, 500, file);
		pile2 = fill_hand_or_deck_or_pile(pile2, line, &amount_of_cards->pile2);
	}
	if (*k > 2) {//zczytywanie kociolkow tak dlugo jak wystepuja
		fgets(line, 500, file);
		pile3 = fill_hand_or_deck_or_pile(pile3, line, &amount_of_cards->pile3);
	}
	if (*k > 3) {//zczytywanie kociolkow tak dlugo jak wystepuja
		fgets(line, 500, file);
		pile4 = fill_hand_or_deck_or_pile(pile4, line, &amount_of_cards->pile4);
	}
	if (*k > 4) {//zczytywanie kociolkow tak dlugo jak wystepuja
		fgets(line, 500, file);
		pile5 = fill_hand_or_deck_or_pile(pile5, line, &amount_of_cards->pile5);
	}
	if (*k > 5) {//zczytywanie kociolkow tak dlugo jak wystepuja
		fgets(line, 500, file);
		pile6 = fill_hand_or_deck_or_pile(pile6, line, &amount_of_cards->pile6);
	}
	fclose(file);
	if (*k > 0) {
		deck = fill_deck(deck, pile1, amount_of_cards->pile1, &s);
	}
	if (*k > 1) {
		deck = fill_deck(deck, pile2, amount_of_cards->pile2, &s);
	}
	if (*k > 2) {
		deck = fill_deck(deck, pile3, amount_of_cards->pile3, &s);
	}
	if (*k > 3) {
		deck = fill_deck(deck, pile4, amount_of_cards->pile4, &s);
	}
	if (*k > 4) {
		deck = fill_deck(deck, pile5, amount_of_cards->pile5, &s);
	}
	if (*k > 5) {
		deck = fill_deck(deck, pile6, amount_of_cards->pile6, &s);
	}
	return s;
}

void number_of_cards(int n,amount amount_of_cards,int k) {
	for (int i = 0; i < n; i++) {//wypisuje ilosc kart gracza
		switch (i) {
		case 0:
			print_players_cards(i + 1, amount_of_cards.hand1, amount_of_cards.deck1);
			break;
		case 1:
			print_players_cards(i + 1, amount_of_cards.hand2, amount_of_cards.deck2);
			break;
		case 2:
			print_players_cards(i + 1, amount_of_cards.hand3, amount_of_cards.deck3);
			break;
		case 3:
			print_players_cards(i + 1, amount_of_cards.hand4, amount_of_cards.deck4);
			break;
		case 4:
			print_players_cards(i + 1, amount_of_cards.hand5, amount_of_cards.deck5);
			break;
		case 5:
			print_players_cards(i + 1, amount_of_cards.hand6, amount_of_cards.deck6);
			break;
		}
	}
	for (int i = 0; i < k; i++) {//wypisuje ilosc kart w kociolkach
		switch (i) {
		case 0:
			print_piles(i + 1, amount_of_cards.pile1);
			break;
		case 1:
			print_piles(i + 1, amount_of_cards.pile2);
			break;
		case 2:
			print_piles(i + 1, amount_of_cards.pile3);
			break;
		case 3:
			print_piles(i + 1, amount_of_cards.pile4);
			break;
		case 4:
			print_piles(i + 1, amount_of_cards.pile5);
			break;
		case 5:
			print_piles(i + 1, amount_of_cards.pile6);
			break;
		}
	}
}

void check_non_greens(int k,colors colors_of_cards) {
	switch (k) {//wypisanie ilosci kart danych kolorow
	case 2:
		if (colors_of_cards.blue == colors_of_cards.red) number_correct(colors_of_cards.blue);
		else number_wrong(k, colors_of_cards);
		break;
	case 3:
		if (colors_of_cards.blue == colors_of_cards.red && colors_of_cards.red == colors_of_cards.violet) number_correct(colors_of_cards.blue);
		else number_wrong(k, colors_of_cards);
		break;
	case 4:
		if (colors_of_cards.blue == colors_of_cards.red && colors_of_cards.red == colors_of_cards.violet && colors_of_cards.violet == colors_of_cards.yellow) number_correct(colors_of_cards.blue);
		else number_wrong(k, colors_of_cards);
		break;
	case 5:
		if (colors_of_cards.blue == colors_of_cards.red && colors_of_cards.red == colors_of_cards.violet && colors_of_cards.violet == colors_of_cards.yellow && colors_of_cards.yellow == colors_of_cards.white) number_correct(colors_of_cards.blue);
		else number_wrong(k, colors_of_cards);
		break;
	case 6:
		if (colors_of_cards.blue == colors_of_cards.red && colors_of_cards.red == colors_of_cards.violet && colors_of_cards.violet == colors_of_cards.yellow && colors_of_cards.yellow == colors_of_cards.white && colors_of_cards.white == colors_of_cards.black) number_correct(colors_of_cards.blue);
		else number_wrong(k, colors_of_cards);
		break;
	}
}

void check_cards_values(deck_of_cards* deck, int g, int s, int k) {
	deck = zero_greens(deck, &g, s);//zeruje zielone karty i zwraca ich ilosc
	deck = sort(deck, s);//sortuje talie wzgledem wartosci
	if (check_values(deck, s, k, g) == 1) print_same_values(deck, s);//wypisywanie wartosci kolorow
	else print_different_values(deck, k, s);
}

void check_loaded_state(int s, int n, int a, int k, int e, amount amount_of_cards,hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6) {
	check check_cards;
	check_cards = { 0,0,0,0,0,0 };
	piles check_pile;
	check_pile = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	check_cards = check_deck(check_cards, s, n);//kazdy gracz dostaje odpowiednia ilosc kart
	int decks = amount_of_cards.deck1 + amount_of_cards.deck2 + amount_of_cards.deck3 + amount_of_cards.deck4 + amount_of_cards.deck5 + amount_of_cards.deck6;
	check_cards = check_decks(check_cards, decks, n);
	int piles = amount_of_cards.pile1 + amount_of_cards.pile2 + amount_of_cards.pile3 + amount_of_cards.pile4 + amount_of_cards.pile5 + amount_of_cards.pile6;
	check_cards = check_piles(check_cards, piles, n, a, k);//odejmuje karty z kociolkow
	int check_players;
	if (check_cards.player1 == amount_of_cards.hand1 && check_cards.player2 == amount_of_cards.hand2 && check_cards.player3 == amount_of_cards.hand3 && check_cards.player4 == amount_of_cards.hand4 && check_cards.player5 == amount_of_cards.hand5 && check_cards.player6 == amount_of_cards.hand6)
		check_players = 1;
	else check_players = 0;
	check_pile = check_pile_colors(check_pile, amount_of_cards, pile1, pile2, pile3, pile4, pile5, pile6);//sprawdza kolory w kociolkach
	check_pile = check_pile_explosion(check_pile, amount_of_cards, pile1, pile2, pile3, pile4, pile5, pile6, e);//sprawdza wybuch kociolka
	int check_colors;
	if (check_pile.colors1 == 0 && check_pile.colors2 == 0 && check_pile.colors3 == 0 && check_pile.colors4 == 0 && check_pile.colors5 == 0 && check_pile.colors6 == 0)
		check_colors = 1;
	else check_colors = 0;
	int check_explosion;
	if (check_pile.explosion1 == 0 && check_pile.explosion2 == 0 && check_pile.explosion3 == 0 && check_pile.explosion4 == 0 && check_pile.explosion5 == 0 && check_pile.explosion6 == 0)
		check_explosion = 1;
	else check_explosion = 0;
	if (check_players == 1 && check_colors == 1 && check_explosion == 1) cout << "Current state of the game is ok" << endl;
	else {
		if (check_players == 0) cout << "The number of players cards on hand is wrong" << endl;
		if (check_colors == 0) print_bad_pile_colors(check_pile);
		if (check_explosion == 0) print_bad_pile_explosion(check_pile);
	}
}

void shuffle_deck(deck_of_cards* deck, int s) {
	int j;
	deck_of_cards temp;
	for (int i = 0; i < s; i++) {
		j = rand() % s;
		temp = deck[i];
		deck[i] = deck[j];
		deck[j] = temp;
	}
}

void create_new_game(int* a, int* n, int* k, int* g, int* gv, int* o, int* e, int* s, deck_of_cards* deck, hand* hand1, hand* hand2, hand* hand3, hand* hand4, hand* hand5, hand* hand6, hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, amount* amount_of_cards) {
	int l;
	*a = 1;//ustawia pierwszego gracza
	cout << "number of players = " << endl; cin >> *n; //liczba graczy
	cout << "number of colors/piles = " << endl; cin >> *k; //liczba kociolkow
	cout << "number of green cards = " << endl; cin >> *g; //liczba zielonych kart
	cout << "value of green cards = " << endl; cin >> *gv; //wartosc zielonych
	cout << "number of cards for non-green cards = " << endl; cin >> *o; //liczba kart dla innych kolorow
	cout << "explosion threshold = " << endl; cin >> *e;//limit kociolkow
	int tab[MAX];
	cout << "cards values: " << endl;
	for (int i = 0; i < *o; i++) {//wczytywanie wartosci kart
		cin >> tab[i];
	}
	*s = *o * *k + *g;//ilosc kart

	//uzupelnienie talii zielonymi kartami
	deck = create_green(deck, *g, *gv);
	//uzupelnienie talii reszta kart
	char color[10] = "blue";//uzupelnianie talii reszta kolorow
	deck = create_deck(deck, color, *o, *g, tab);
	strcpy(color, "red");
	if (*k > 1) deck = create_deck(deck, color, *o, *o + *g, tab);
	strcpy(color, "violet");
	if (*k > 2) deck = create_deck(deck, color, *o, 2 * *o + *g, tab);
	strcpy(color, "yellow");
	if (*k > 3) deck = create_deck(deck, color, *o, 3 * *o + *g, tab);
	strcpy(color, "white");
	if (*k > 4) deck = create_deck(deck, color, *o, 4 * *o + *g, tab);
	strcpy(color, "black");
	if (*k > 5) deck = create_deck(deck, color, *o, 5 * *o + *g, tab);
	print_deck(deck, *s); //zapisanie talii
	shuffle_deck(deck, *s);//potasowanie talii
	for (int i = 0; i < *s; i++)//rozdanie kart
	{
		l = i % *n;
		switch (l) {
		case 0:
			hand1 = add_card(hand1, i, deck, amount_of_cards->hand1);
			amount_of_cards->hand1++;
			break;
		case 1:
			hand2 = add_card(hand2, i, deck, amount_of_cards->hand2);
			amount_of_cards->hand2++;
			break;
		case 2:
			hand3 = add_card(hand3, i, deck, amount_of_cards->hand3);
			amount_of_cards->hand3++;
			break;
		case 3:
			hand4 = add_card(hand4, i, deck, amount_of_cards->hand4);
			amount_of_cards->hand4++;
			break;
		case 4:
			hand5 = add_card(hand5, i, deck, amount_of_cards->hand5);
			amount_of_cards->hand5++;
			break;
		case 5:
			hand6 = add_card(hand6, i, deck, amount_of_cards->hand6);
			amount_of_cards->hand6++;
			break;
		}
	}
}

int find_the_lowest(hand* hand0, int n, int *p) {
	int u=0, m = 100;
	for (int i = 0; i < n; i++) {
		if (hand0[i].value == m) (*p)++;
		if (hand0[i].value < m) {
			m = hand0[i].value;
			u = i;
			*p=0;
		}
	}
	return u;
}

int find_the_highest(hand* hand0, int n, int* p) {
	int u=0, m = 0;
	for (int i = 0; i < n; i++) {
		if (hand0[i].value == m) (*p)++;
		if (hand0[i].value > m) {
			m = hand0[i].value;
			u = i;
			*p = 0;
		}
	}
	return u;
}

void swap_cards(hand* hand0, int i) {
	hand temp;
	temp = hand0[0];
	hand0[0] = hand0[i];
	hand0[i] = temp;
}

piles_sums count_piles(piles_sums pile_sum, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile6, hand* pile5, amount amount_of_cards) {
	for (int i = 0; i < amount_of_cards.pile1; i++) {
		pile_sum.first += pile1[i].value;
	}
	for (int i = 0; i < amount_of_cards.pile2; i++) {
		pile_sum.second += pile2[i].value;
	}
	for (int i = 0; i < amount_of_cards.pile3; i++) {
		pile_sum.third += pile3[i].value;
	}
	for (int i = 0; i < amount_of_cards.pile4; i++) {
		pile_sum.fourth += pile4[i].value;
	}
	for (int i = 0; i < amount_of_cards.pile5; i++) {
		pile_sum.fifth += pile5[i].value;
	}
	for (int i = 0; i < amount_of_cards.pile6; i++) {
		pile_sum.sixth += pile6[i].value;
	}
	return pile_sum;
}

int check_pile_sum(int m, piles_sums pile_sum) {
	if (m == 1) return pile_sum.first;
	if (m == 2) return pile_sum.second;
	if (m == 3) return pile_sum.third;
	if (m == 4) return pile_sum.fourth;
	if (m == 5) return pile_sum.fifth;
	if (m == 6) return pile_sum.sixth;
	return -1;
}

int find_another_lowest(hand* hand0, int n, int u, hand lowest) {
	for (int i = u+1; i < n; i++) {
		if (hand0[i].value == lowest.value) {
			return i;
		}
	}
	return -1;
}

int find_another_highest(hand* hand0, int n, int u, hand lowest) {
	for (int i = u + 1; i < n; i++) {
		if (hand0[i].value == lowest.value) {
			return i;
		}
	}
	return -1;
}

int find_highest_or_lowest_card(hand* hand0, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, amount amount_of_cards, int n, int k, int *player) {
	int u, p = 0, q, min, c=0, m;
	piles_sums pile_sum = { 0,0,0,0,0,0 };
	pile_sum = count_piles(pile_sum, pile1, pile2, pile3, pile4, pile5, pile6, amount_of_cards);
	if(*player==0) u = find_the_lowest(hand0, n, &p);//znajdujemy najmiejsza
	else u = find_the_highest(hand0, n, &p);//znajdujemy najwieksza
	min = 1000;
	if (p != 0) {
		for (int i = 0; i < p + 1; i++) {
			m = check_which_pile(hand0[u], k, pile1, pile2, pile3, pile4, pile5, pile6, amount_of_cards, pile_sum);
			q = check_pile_sum(m, pile_sum);
			if (q < min) {
				min = q;
				c = u;
			}
			if (*player == 0) u = find_another_lowest(hand0, n, u, hand0[u]);
			else u = find_another_highest(hand0, n, u, hand0[u]);
		}
	}
	if (p != 0) u = c;
	if (*player == 0) *player = 1;
	else if (*player == 1) *player = 0;
	return u;
}

void player_move(int x,int a, int k, int e, amount* amount_of_cards, hand* hand1, hand* hand2, hand* hand3, hand* hand4, hand* hand5, hand* hand6, hand* deck1, hand* deck2, hand* deck3, hand* deck4, hand* deck5, hand* deck6, hand* pile1, hand* pile2, hand* pile3, hand* pile4, hand* pile5, hand* pile6, check *highest) {
	int m,u;
	piles_sums pile_sum = { 0,0,0,0,0,0 };
	pile_sum = count_piles(pile_sum, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards);//zlicza sume kart w kociolkach
	switch (a) {
	case 1:
		if (x == 1) {//jesli gracz chce rzucic najmniejsza lub najwieksza po zagraniu wybuchu kociolka
			u = find_highest_or_lowest_card(hand1, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, amount_of_cards->hand1, k, &highest->player1);
		}
		else u = 0;//jesli gracz rzuca pierwsza karte
		if (x != 0) swap_cards(hand1, u);
		m = check_which_pile(hand1[0], k, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, pile_sum);
		put_card_on_pile(amount_of_cards, m, hand1[0], pile1, pile2, pile3, pile4, pile5, pile6);
		remove_card_from_hand(&amount_of_cards->hand1, hand1);
		if_explosion_clear_pile(e, deck1, &amount_of_cards->deck1, amount_of_cards, m, pile1, pile2, pile3, pile4, pile5, pile6, &highest->player1);
		break;
	case 2:
		if (x == 1) {
			u = find_highest_or_lowest_card(hand2, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, amount_of_cards->hand2, k, &highest->player2);
		}
		else u = 0;
		if (x != 0) swap_cards(hand2, u);
		m = check_which_pile(hand2[0], k, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, pile_sum);
		put_card_on_pile(amount_of_cards, m, hand2[0], pile1, pile2, pile3, pile4, pile5, pile6);
		remove_card_from_hand(&amount_of_cards->hand2, hand2);
		if_explosion_clear_pile(e, deck2, &amount_of_cards->deck2, amount_of_cards, m, pile1, pile2, pile3, pile4, pile5, pile6, &highest->player2);
		break;
	case 3:
		if (x == 1) {
			u = find_highest_or_lowest_card(hand3, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, amount_of_cards->hand3, k, &highest->player3);
		}
		else u = 0;
		if (x != 0) swap_cards(hand3, u);
		m = check_which_pile(hand3[0], k, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, pile_sum);
		put_card_on_pile(amount_of_cards, m, hand3[0], pile1, pile2, pile3, pile4, pile5, pile6);
		remove_card_from_hand(&amount_of_cards->hand3, hand3);
		if_explosion_clear_pile(e, deck3, &amount_of_cards->deck3, amount_of_cards, m, pile1, pile2, pile3, pile4, pile5, pile6, &highest->player3);
		break;
	case 4:
		if (x == 1) {
			u = find_highest_or_lowest_card(hand4, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, amount_of_cards->hand4, k, &highest->player4);
		}
		else u = 0;
		if (x != 0) swap_cards(hand4, u);
		m = check_which_pile(hand4[0], k, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, pile_sum);
		put_card_on_pile(amount_of_cards, m, hand4[0], pile1, pile2, pile3, pile4, pile5, pile6);
		remove_card_from_hand(&amount_of_cards->hand4, hand4);
		if_explosion_clear_pile(e, deck4, &amount_of_cards->deck4, amount_of_cards, m, pile1, pile2, pile3, pile4, pile5, pile6, &highest->player4);
		break;
	case 5:
		if (x == 1) {
			u = find_highest_or_lowest_card(hand5, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, amount_of_cards->hand5, k, &highest->player5);
		}
		else u = 0;
		if (x != 0) swap_cards(hand5, u);
		m = check_which_pile(hand5[0], k, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, pile_sum);
		put_card_on_pile(amount_of_cards, m, hand5[0], pile1, pile2, pile3, pile4, pile5, pile6);
		remove_card_from_hand(&amount_of_cards->hand5, hand5);
		if_explosion_clear_pile(e, deck5, &amount_of_cards->deck5, amount_of_cards, m, pile1, pile2, pile3, pile4, pile5, pile6, &highest->player5);
		break;
	case 6:
		if (x == 1) {
			u = find_highest_or_lowest_card(hand6, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, amount_of_cards->hand6, k, &highest->player6);
		}
		else u=0;
		if (x != 0) swap_cards(hand6, u);
		m = check_which_pile(hand6[0], k, pile1, pile2, pile3, pile4, pile5, pile6, *amount_of_cards, pile_sum);
		put_card_on_pile(amount_of_cards, m, hand6[0], pile1, pile2, pile3, pile4, pile5, pile6);
		remove_card_from_hand(&amount_of_cards->hand6, hand6);
		if_explosion_clear_pile(e, deck6, &amount_of_cards->deck6, amount_of_cards, m, pile1, pile2, pile3, pile4, pile5, pile6, &highest->player6);
		break;
	}
}

int main()
{
	srand(time(NULL));
	deck_of_cards* deck = create_new_deck();
	amount amount_of_cards;
	amount_of_cards = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	colors colors_of_cards;
	colors_of_cards = { 0,0,0,0,0,0 };
	hand* hand1 = create_hand_deck_pile();
	hand* hand2 = create_hand_deck_pile();
	hand* hand3 = create_hand_deck_pile();
	hand* hand4 = create_hand_deck_pile();
	hand* hand5 = create_hand_deck_pile();
	hand* hand6 = create_hand_deck_pile();
	hand* deck1 = create_hand_deck_pile();
	hand* deck2 = create_hand_deck_pile();
	hand* deck3 = create_hand_deck_pile();
	hand* deck4 = create_hand_deck_pile();
	hand* deck5 = create_hand_deck_pile();
	hand* deck6 = create_hand_deck_pile();
	hand* pile1 = create_hand_deck_pile();
	hand* pile2 = create_hand_deck_pile();
	hand* pile3 = create_hand_deck_pile();
	hand* pile4 = create_hand_deck_pile();
	hand* pile5 = create_hand_deck_pile();
	hand* pile6 = create_hand_deck_pile();
	int n, k, g, gv, o, s, a, e;
	int x;
	cout << "Press 1 to create new deck or 2 in order to load state of the game." << endl; cin >> x;
	switch (x) {
	case 1://tworzenie nowej rozgrywki
		create_new_game(&a, &n, &k, &g, &gv, &o, &e, &s, deck, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5, pile6, &amount_of_cards);
		print_state_of_the_game(a, n, e, k, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5, pile6, amount_of_cards);
		break;
	case 2://wczytanie stanu gry
		s=load_game(&a, &n, &e, &k, deck, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5, pile6, &amount_of_cards, colors_of_cards);
		print_state_of_the_game(a, n, e, k, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5, pile6, amount_of_cards);
		break;
	}
	colors_of_cards = { 0,0,0,0,0,0 };
	check_number_of_colors(deck, &colors_of_cards, s);

	cout << "Press 1 to check number of cards on hands, in decks and on piles, else press 0." << endl; cin >> x;
	if (x == 1) number_of_cards(n, amount_of_cards, k);	//sprawdza ilosc kart na stosach
	
	cout << "Press 1 to check green cards amount and value, else press 0." << endl; cin >> x;
	gv = find_one_green_card(deck, s);//sprawdza czy istnieja zielone karty
	g = check_green_cards(deck, gv, s);
	if (x == 1) {
		if (gv == 0) {
			cout << "Green cards does not exist" << endl;
		}
		else {
			if (g == 0) cout << "Different green cards values occurred" << endl;
			else cout << "Found " << g << " green cards, all with " << gv << " value" << endl;
		}
	}
	
	cout << "Press 1 to check number of non-green cards, else press 0." << endl; cin >> x;
	if (x == 1) check_non_greens(k, colors_of_cards);//sprawdza wartosci niezielonych kart

	cout << "Press 1 to check cards values, else press 0." << endl; cin >> x;
	if (x == 1) check_cards_values(deck, g, s, k);//sprawdza wartosci niezielonych kart
	
	cout << "Press 1 to check if loaded state of the game is right, else press 0." << endl; cin >> x;
	if (x == 1) check_loaded_state(s, n, a, k, e, amount_of_cards, pile1, pile2, pile3, pile4, pile5 ,pile6); //sprawdzanie stanu gry
		
	check highest;
	highest = { 0,0,0,0,0,0 };
	//wykonanie ruchu
	while ((amount_of_cards.hand1 + amount_of_cards.hand2 + amount_of_cards.hand3 + amount_of_cards.hand4 + amount_of_cards.hand5 + amount_of_cards.hand6) != 0) {
		cout << "Press 1 to choose the lowest card(the highest if previous omve with lowest made the pile explode) or 0 to choose first card on the hand." << endl; cin >> x;
		s = load_game(&a, &n, &e, &k, deck, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5, pile6, &amount_of_cards, colors_of_cards);
		if ((amount_of_cards.hand1 + amount_of_cards.hand2 + amount_of_cards.hand3 + amount_of_cards.hand4 + amount_of_cards.hand5 + amount_of_cards.hand6) == 0)break;
		player_move(x, a, k, e, &amount_of_cards, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5, pile6, &highest);
		a++;
		if (a > n) a = 1;//aktywny gracz
		print_state_of_the_game(a, n, e, k, hand1, hand2, hand3, hand4, hand5, hand6, deck1, deck2, deck3, deck4, deck5, deck6, pile1, pile2, pile3, pile4, pile5,pile6,amount_of_cards);
	}

	//koniec gry
	end_of_the_game(n, deck1, deck2, deck3, deck4, deck5, deck6, amount_of_cards);
	
	free(hand1);
	free(hand2);
	free(hand3);
	free(hand4);
	free(hand5);
	free(hand6);
	free(deck1);
	free(deck2);
	free(deck3);
	free(deck4);
	free(deck5);
	free(deck6);
	free(pile1);
	free(pile2);
	free(pile3);
	free(pile4);
	free(pile5);
	free(pile6);
	free(deck);
	return 0;
}



