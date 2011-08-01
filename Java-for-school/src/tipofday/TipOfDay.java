
//Title:       Top of Day
//Version:     1.0
//Copyright:   Copyright (c)
//Author:      Jesse Gumm
//Company:
//Description:
package tipofday;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class TipOfDay extends Applet {
  boolean isStandalone = false;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public TipOfDay() {
  }

  //Initialize the applet
  public void init()
  {

    Frame f = new Frame();
    NewDialog d = new NewDialog(f,"Tip of the day",false);
    d.setLayout(new GridLayout(2,1,10,1));
    d.add(new Label("Don't bet on the races"));
    d.add(new Label("Java is cool"));
    Button b = new Button("OK");
    Button bb = new Button("Open");
    d.add(b);
    d.add(bb);
    b.addActionListener(d);
    bb.addActionListener(d);
    d.setSize(200,100);
    d.show();

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