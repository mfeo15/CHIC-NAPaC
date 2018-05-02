bool parent_game_request(){
  blink_LED(0,purple);
  Serial.println("Parent requested game session");
  int c = 0;
  //accept_game_message();
  
  while ( !presence()){
    blink_LED(0,purple);
    c++;
  }
//  if ( c = 100){
//    Serial.println("No answer from child");
//    return 0;
//  }
  Serial.println("Child accepted game session!");
  accept_game_message();
  blink_LED(0,yellow);
  return 1;
}

