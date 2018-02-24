public class Player {
  
  final int MAX_DIST = 20;
  
  private AudioPlayer player;
  boolean activated = false;
  
  /*
   * Constructor
   */
  public Player(AudioPlayer player){
    this.player = player;
  }
  
  public void play(int distance) {
    
    if(!activated) {  // If the note is not active
      
      if (distance < MAX_DIST && distance > 0){  // If someone activate the note
        //player.rewind();
        player.play();
        activated = true;
      }
      
    } else {
      
      if (!player.isPlaying()){
        
        if (distance > MAX_DIST || distance < 0){   // If no one is on the note
          player.rewind();
          activated = false;
        }
      }
      
    }
    
    
    
    
    
  }
  
  
}