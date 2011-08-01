
//Title:       Text Transfer Applet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description: Text Transfer Applet Exercise #7
package textransfer;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class TextTransfer extends Applet implements ActionListener{
  boolean isStandalone = false;
  TextArea textArea;
  List list;
  Button transferbutton; // this is the button that does the actual transfer
  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public TextTransfer() {
  }

  //Initialize the applet
  public void init()
  {
    transferbutton = new Button("Transfer Selected");
    textArea=new TextArea("",10,15);
    list = new List(10,true);
    list.add("These");
    list.add("Are");
    list.add("The");
    list.add("Ten");
    list.add("Words");
    list.add("From");
    list.add("Which");
    list.add("You");
    list.add("Can");
    list.add("Choose");
    add(list);
    add(textArea);
    add(transferbutton);
    list.addActionListener(this);
    transferbutton.addActionListener(this);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  public void actionPerformed(ActionEvent e)
  {
    int i;
    int x;
    if(e.getSource() == transferbutton) // if the action is the buttonpress
    {
      for(i=0;i<list.getItemCount();i++) // through all items in list
        if(list.isIndexSelected(i)) // if it is selected
          transferWord(i);   // transfer it over
    }
  }

  // transfer the item in the list with the designated index
  public void transferWord(int index)
  {
    // this is a little cleaner than the exercise in the book
     textArea.append(list.getItem(index) + '\n');
  }


  //Component initialization
  private void jbInit() throws Exception {
  }

  //Start the applet
  public void start() {
  }

  //Stop the applet
  public void stop() {
  }

  //Destroy the applet
  public void destroy() {
  }

  //Get Applet information
  public String getAppletInfo() {
    return "Applet Information";
  }

  //Get parameter info
  public String[][] getParameterInfo() {
    return null;
  }
}