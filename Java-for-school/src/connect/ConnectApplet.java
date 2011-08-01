
//Title:       Connect Applet
//Version:     1.0
//Copyright:   Copyright (c) Jesse Gumm
//Author:      Jesse Gumm
//Company:
//Description:
package connect;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.net.*;

public class ConnectApplet extends Applet implements ActionListener{
  boolean isStandalone = false;
  boolean badURL;
  TextField tf;

  //Get a parameter value
  public String getParameter(String key, String def) {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public ConnectApplet() {
  }

  //Initialize the applet
  public void init() {
    tf=new TextField("",40);
    Button b=new Button("Connect");
    Button fav=new Button("Favorite");
    add(tf);
    add(fav);
    add(b);
    b.addActionListener(this);
    fav.addActionListener(this);
    badURL=false;
    setBackground(Color.white);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  public void paint( Graphics g)
  {
    Font f=new Font("TimesRoman",Font.PLAIN,24);
    g.setFont(f);
    int height=f.getSize();
    if(badURL)
      g.drawString("BADURL",60,130);
    else
      g.drawString("Type URL to connect to",25,130);
  }

  public void actionPerformed(ActionEvent e)
  {
    Button s=(Button)e.getSource();
    String str;
    if(s.getLabel()=="Connect")
      str=tf.getText();
    else
      str="www.penny-arcade.com";
    try
    {
      URL url=new URL("Http://"+str);
      AppletContext context = getAppletContext();
      context.showDocument(url);
    }
    catch(MalformedURLException e1)
    {
      badURL = true;
      repaint();
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