import ddf.minim.*;
import processing.serial.*;


  Minim minim = new Minim(this);
  
  ArrayList<AudioPlayer> notes = new ArrayList<AudioPlayer>();  // The arraylist cointaining the notes to be played
  ArrayList<Player> players = new ArrayList<Player>();
  //----Call serial class----
  Serial myPort;             // Create object from serial class
  String val ;               // Data received from the serial port
  
  //----Array to contain distance data----
  float num;
  String[] sdata;
  int[] fdata;
  
  
void setup(){
  
  String portName = "COM3";
  myPort = new Serial(this, portName, 115200);
  
  /*
   * Loading the notes into the ArrayList
   */
  notes.add(minim.loadFile("piano-notes/better-notes/do.wav"));
  notes.add(minim.loadFile("piano-notes/better-notes/re.wav")); 
  //notes.add(minim.loadFile("piano-notes/newe.wav")); 
  //notes.add(minim.loadFile("piano-notes/newf.wav")); 
  //notes.add(minim.loadFile("piano-notes/newg.wav")); 
  //notes.add(minim.loadFile("piano-notes/newc.wav")); 
  //notes.add(minim.loadFile("piano-notes/newc.wav")); 
  
  /*
   * Initializing the players
   */
  for (AudioPlayer i : notes){
    players.add(new Player(i));
  }
  
  delay(2000);
  
}



void draw()
{

  if (myPort.available() > 0) {          // If data is available.
    val = myPort.readStringUntil('\n');  // Read the serial input.
    
    if (val != null) {
      parseData(val);
      //println(val);
    }
    
    playSound();
    
  }  
}



/**
 * Parse the CSV data int an int array.
 * @param the csv string.
 **/
void parseData(String data){
  sdata = split(data, ",");           //Split Data
  fdata = int(sdata);                 //Convert Data from String to int
}


/**
 * Assign every measurements to each player.
 **/
void playSound(){
  
  int i = 0;
    for (Player pl : players){
      println(fdata);
      pl.play(fdata[i]);
      i++;
    }
    
}