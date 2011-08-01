
//Title:        KeyApplet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package keyapplet;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;

public class KeyApplet extends Applet implements KeyListener {
  boolean isStandalone = false;
  String line = "Wang Chung";
  int downkey;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public KeyApplet() {
  }

  //Initialize the applet
  public void init() {
    Font f = new Font("TimesRoman",Font.BOLD,32);
    setFont(f);
    addKeyListener(this);
    downkey=0;
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }
  public void keyReleased(KeyEvent e)
  {
    if( e.getKeyChar() == KeyEvent.VK_CONTROL ||
        e.getKeyChar() == KeyEvent.VK_SHIFT)
      downkey=0;
  }

  public void keyPressed(KeyEvent e)
  {
    if( e.getKeyChar() == KeyEvent.VK_CONTROL ||
        e.getKeyChar() == KeyEvent.VK_SHIFT)
      downkey=e.getKeyChar();
  }

  public void keyTyped(KeyEvent e)
  {
    line="";
    if(downkey == KeyEvent.VK_CONTROL)
      line+="Control ";
    else if(downkey == KeyEvent.VK_SHIFT)
      line+="Shift ";
    line+=e.getKeyChar();
    repaint();
  }

  public void paint(Graphics g)
  {
    g.drawString(line,20,100);
  }

  //Component initialization
  private void jbInit() throws Exception {
    this.setSize(new Dimension(400,300));
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