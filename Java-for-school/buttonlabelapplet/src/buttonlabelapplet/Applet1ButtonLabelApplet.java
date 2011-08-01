
//Title:       Button Label Applet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description: Button and LAbel Applet homework
package buttonlabelapplet;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class Applet1ButtonLabelApplet extends Applet implements ActionListener {
  boolean isStandalone = false;
  Button [] button = new Button[3]; // implement Buttons and LAbels as arrays
  Label [] label = new Label[3];

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public Applet1ButtonLabelApplet() {
  }

  //Initialize the applet
  public void init()
  {
    // Loop to get all buttons and labels
    for(int i=0;i<3;i++)
    {
      //Create Button an Label Names
      button[i] = new Button("Button" + String.valueOf(i+1));
      label[i] = new Label("Label" + String.valueOf(i+1));
      //Add Buttons to applet
      add(button[i]);
      add(label[i]);
      button[i].addActionListener(this);
    }
    //Set Colors on buttons and labels
    button[0].setBackground(Color.green);
    button[1].setBackground(Color.blue);
    button[2].setBackground(Color.magenta);
    label[0].setForeground(Color.magenta);
    label[1].setForeground(Color.orange);
    label[1].setForeground(Color.gray);

    setBackground(Color.white);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  //Component initialization
  private void jbInit() throws Exception {
  }

  //Start the applet
  public void start()
  {
    // Move the buttons and labels so they line up.
    for(int i=0;i<3;i++)
    {
      label[i].setLocation(90*i +10,100);
      button[i].setLocation(90 * i + 10,10);
      button[i].setSize(80,25);
    }
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

  public void actionPerformed(ActionEvent e)
  {
    // Much less time consuming than writing out everything

    Button b= (Button) e.getSource();
    String str="";
    str=b.getLabel();
    // Find Interger value of the last character in the Button Label
    int i=(int)str.charAt(str.length()-1)-49;
    // Switch the two label of the button and text of label
    // 'str' is serving as a temp value for ButtonX
    button[i].setLabel(label[i].getText());
    label[i].setText(str);
  }
  //Get parameter info
  public String[][] getParameterInfo() {
    return null;
  }
}