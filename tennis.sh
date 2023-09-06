#!/bin/bash
# Dan Saada 208968560

onGame=true
ball=0
player1Point=50
player2Point=50
player1Choose=0
player2Choose=0

print_middle() {
    case $ball in
        3)
        echo " |       |       #       |       |O"
        ;;
        2)
        echo " |       |       #       |   O   | "
        ;;
        1)
        echo " |       |       #   O   |       | "
        ;;
        0)
        echo " |       |       O       |       | "
        ;;
        -1)
        echo " |       |   O   #       |       | "
        ;;
        -2)
        echo " |   O   |       #       |       | "
        ;;
        -3)
        echo "O|       |       #       |       | "
        ;;
    esac
}

print_board () {

  print_points_left
  echo " --------------------------------- "
  echo " |       |       #       |       | "
  echo " |       |       #       |       | "
  print_middle
  echo " |       |       #       |       | "
  echo " |       |       #       |       | "
  echo " --------------------------------- "
}

print_points_left() {
    echo " Player 1: ${player1Point}         Player 2: ${player2Point} "
}

print_choose() {
    echo -e "       Player 1 played: ${player1Choose}\n       Player 2 played: ${player2Choose}\n\n"
}

match() {

    player1Point=$((player1Point - player1Choose))
    player2Point=$((player2Point - player2Choose))

    if [[ $player1Choose -gt $player2Choose ]]; then
        ball=$((ball + 1))
        if [[ $ball -le 0 ]]; then
            ball=1
        fi
    elif [[ $player2Choose -gt $player1Choose ]]; then
        ball=$((ball - 1))
        if [[ $ball -ge 0 ]]; then
            ball=-1
        fi
    fi
}

check_for_win() {

    win=0
    
    if [[ $ball == 3 ]]; then 
        win=1

    elif [[ $ball == -3 ]]; then 
        win=2

    elif [[ $player1Point == 0 && $player2Point != 0 ]]; then
        win=2

    elif [[ $player2Point == 0 && $player1Point != 0 ]]; then
        win=1        

    elif [[ $player2Point == 0 && $player1Point == 0 ]]; then
        if [[ $ball -gt 0 ]]; then
            win=1

        elif [[ $ball -lt 0 ]]; then
            win=2
        
        else 
            win=3
        fi
    fi

  result
}

result(){
   case $win in
        3)
        echo "IT'S A DRAW !"
        onGame=false
        ;;
        2)
        echo "PLAYER 2 WINS !"
        onGame=false
        ;;
        1)
        echo "PLAYER 1 WINS !"
        onGame=false
        ;;
        esac
}

players_pick(){

    valid=false

    while ! $valid;
    do
        echo "PLAYER 1 PICK A NUMBER: "
        read -s player1Choose
        if [[ $player1Choose =~ ^[0-9]+$ ]]; then
            if [[ $player1Choose -le $player1Point ]]; then
                break
            fi
        fi
        echo "NOT A VALID MOVE !"
    done

    while ! $valid;
    do
        echo "PLAYER 2 PICK A NUMBER: "
        read -s player2Choose
        if [[ $player2Choose =~ ^[0-9]+$ ]]; then
            if [[ $player2Choose -le $player2Point ]]; then
                break
            fi
        fi
        echo "NOT A VALID MOVE !"
    done
    
    
}

game_logic(){
    players_pick
    match
    print_board
    print_choose
    check_for_win
}

game() {

    print_board
    
    #while there is no result yet to the game
    while $onGame;
    do
    game_logic
    done
}

game


