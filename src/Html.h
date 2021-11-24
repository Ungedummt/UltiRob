#include <Arduino.h>

/*String quiz_type = "normal";
String PlayerWrongNextPlayserbyReset = "false";
String PlayersCanSeeDelays = "false";
String PlayersPressMultipleTimes = "true";*/

String web_basics;
String web_dmx;
String web_actions;
String web_login;

static const String head = "<!DOCTYPE html><html lang='en'>";

static const String disconnect = "<a href='/login?DISCONNECT=YES'>disconnect</a>";

static const String main_header = "\
<head>\
  <meta http-equiv='content-type' content='text/html; charset=UTF-8'>\
  <meta charset='utf-8'>\
  <title>Configuration</title>\
</head>\
";

static const String login_header = "\
<head>\
  <meta http-equiv='content-type' content='text/html; charset=UTF-8'>\
  <meta charset='utf-8'>\
  <title>Login</title>\
</head>\
";

static const String style = "<style>*{font-family:Ubuntu,Calibri,Noto Sans;font-size:19px;margin:0;padding:0;cursor:default;color:#000}#body{border-top-color:#37f;border-top-style:solid;border-top-width:5px;background:#fff;border-radius:5px;width:700px;margin:28px auto 78px}body{background-color:#add8e6}a{font-weight:700;border-radius:5px;border:none;text-align:center;text-decoration:none;display:inline-block;cursor:pointer;line-height:50px;font-size:25px;color:#000}.grid{display:grid}.bold{font-weight:bolder}#nav-bar{display:grid;grid-template-columns:auto auto auto auto auto auto;grid-gap:10px;padding:20px 20px 0}#nav-bar a{background:#add8e6}#nav-bar .active{background:red}#nav-bar #game{grid-column-start:1;grid-column-end:4}#nav-bar #configuration{grid-column-start:4;grid-column-end:7}#nav-bar #basics{grid-column-start:-7;grid-column-end:-5}#nav-bar #actions{grid-column-start:-5;grid-column-end:-3}#nav-bar #dmx{grid-column-start:-3;grid-column-end:-1}#content{display:grid;grid-gap:10px;padding:20px 30px}#content legend{padding-left:4px;margin:0 auto;padding-right:8px;font-size:21px}#content fieldset{border-radius:5px;border-width:2px;border-color:#37f;border-style:solid}#content select{width:100%}#content p{font-size:16px}#content input[type=number]{width:80%}#content input[type=checkbox]{margin:auto;zoom:1.5;transform:scale(1.5)}#content input[type=color]{width:100%;height:100%}#content #mar{display:block;width:95%;margin:10px auto 15px}#content #mar #boxes{grid-template-columns:auto 12%;grid-gap:10px}#content #mar #boxes p{line-height:30px}#content #mar #boxes #ch_pos{grid-column-start:1;grid-column-end:3;text-align:center;margin-top:25px;margin-bottom:-5px;font-size:20px}#content #mar #boxes #ch_pos_grid{grid-template-columns:auto auto auto auto auto;grid-column-start:1;grid-column-end:3;text-align:center}#content #mar #boxes #ch_pos_grid input{height:35px}#content #test_dmx input{font-weight:700;border-radius:5px;border:none;text-align:center;text-decoration:none;display:inline-block;cursor:pointer;line-height:50px;font-size:25px;background:#ff0;margin:0 auto;width:50%;display:block}#save_discard{display:grid;grid-template-columns:auto auto;grid-gap:10px;padding:0 20px 20px}#save_discard input{font-weight:700;border-radius:5px;border:none;text-align:center;text-decoration:none;display:inline-block;cursor:pointer;line-height:50px;font-size:25px}#save_discard #save{background:green}#save_discard #discard{background:red}.login-block{width:340px;padding:20px;background:#fff;border-radius:5px;border-top:5px solid #37f;margin:0 auto;margin-top:50px}.login-block input,.login-block button{width:100%;height:50px;box-sizing:border-box;border-radius:5px;font-size:16px;outline:none}.login-block h1{text-align:center;color:#000;font-size:22px;text-transform:uppercase;margin-top:2px;margin-bottom:25px}.login-block input{border:1px solid #ccc;margin-bottom:20px;padding:0 20px 0 15px;cursor:text}.login-block input:active,.login-block input:focus{border:1px solid #37f}.login-block button{border:0;background:#37f;color:#fff;font-weight:700;text-transform:uppercase;cursor:pointer;background:#37f}.login-block button:hover{background:#6397ff}.main-block{width:98%;background:#fff;border-radius:5px;margin:0 auto;margin-bottom:60px}.footer{position:fixed;bottom:0;width:100%;background-color:#ff0;display:inline-block}.footer p{margin-right:15px;text-align:right;line-height:50px;width:auto;float:right;cursor:help}.footer img{float:right;padding:12.5px;height:25px;cursor:help}</style>";

/*"\
<style>\
* {\
  font-family: Ubuntu, Calibri, Noto Sans;\
  font-size: 19px;\
  margin: 0;\
  padding: 0;\
  cursor: default;\
  color: #000;\
}\
\
#body {\
  border-top-color: #37f;\
  border-top-style: solid;\
  border-top-width: 5px;\
  background: #fff;\
  border-radius: 5px;\
  width: 700px;\
  margin: 28px auto 78px;\
}\
\
body {\
  background-color: #add8e6;\
}\
\
a {\
  font-weight: 700;\
  border-radius: 5px;\
  border: none;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  cursor: pointer;\
  line-height: 50px;\
  font-size: 25px;\
  color: #000;\
}\
\
.grid {\  display: grid;\
}\
\
.bold {\
  font-weight: bolder;\
}\
\
#nav-bar {\
  display: grid;\
  grid-template-columns: auto auto auto auto auto auto;\
  grid-gap: 10px;\
  padding: 20px 20px 0;\
}\
\
#nav-bar a {\
  background: #add8e6;\
}\
\
#nav-bar .active {\
  background: red;\
}\
\
#nav-bar #game {\
  grid-column-start: 1;\
  grid-column-end: 4;\
}\
\
#nav-bar #configuration {\
  grid-column-start: 4;\
  grid-column-end: 7;\
}\
\
#nav-bar #basics {\
  grid-column-start: -7;\
  grid-column-end: -5;\
}\
\
#nav-bar #actions {\
  grid-column-start: -5;\
  grid-column-end: -3;\
}\
\
#nav-bar #dmx {\
  grid-column-start: -3;\
  grid-column-end: -1;\
}\
\
#content {\
  display: grid;\
  grid-gap: 10px;\
  padding: 20px 30px;\
}\
\
#content legend {\
  padding-left: 4px;\
  margin: 0 auto;\
  padding-right: 8px;\
  font-size: 21px;\
}\
\
#content fieldset {\
  border-radius: 5px;\
  border-width: 2px;\
  border-color: #37f;\
  border-style: solid;\
}\
\
#content select {\
  width: 100%;\
}\
\
#content p {\
  font-size: 16px;\
}\
\
#content input[type='number'] {\
  width: 80%;\
}\
\
#content input[type='checkbox'] {\
  margin: auto;\
  zoom: 1.5;\
  transform: scale(1.5);\
}\
\
#content input[type='color'] {\
  width: 100%;\
  height: 100%;\
}\
\
#content #mar {\
  display: block;\
  width: 95%;\
  margin: 10px auto 15px;\
}\
\
#content #mar #boxes {\
  grid-template-columns: auto 12%;\
  grid-gap: 10px;\
}\
\
#content #mar #boxes p {\
  line-height: 30px;\
}\
\
#content #mar #boxes #ch_pos {\
  grid-column-start: 1;\
  grid-column-end: 3;\
  text-align: center;\
  margin-top: 25px;\
  margin-bottom: -5px;\
  font-size: 20px;\
}\
\
#content #mar #boxes #ch_pos_grid {\
  grid-template-columns: auto auto auto auto auto;\
  grid-column-start: 1;\
  grid-column-end: 3;\
  text-align: center;\
}\
\
#content #mar #boxes #ch_pos_grid input {\
  height: 35px;\
}\
\
#content #test_dmx input {\
  font-weight: 700;\
  border-radius: 5px;\
  border: none;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  cursor: pointer;\
  line-height: 50px;\
  font-size: 25px;\
  background: #ff0;\
  margin: 0 auto;\
  width: 50%;\
  display: block;\
}\
\
#save_discard {\
  display: grid;\
  grid-template-columns: auto auto;\
  grid-gap: 10px;\
  padding: 0 20px 20px;\
}\
\
#save_discard input {\
  font-weight: 700;\
  border-radius: 5px;\
  border: none;\
  text-align: center;\
  text-decoration: none;\
  display: inline-block;\
  cursor: pointer;\
  line-height: 50px;\
  font-size: 25px;\
}\
\
#save_discard #save {\
  background: green;\
}\
\
#save_discard #discard {\
  background: red;\
}\
\
.login-block {\
  width: 340px;\
  padding: 20px;\
  background: #fff;\
  border-radius: 5px;\
  border-top: 5px solid #37f;\
  margin: 0 auto;\
  margin-top: 50px;\
}\
\
.login-block input,\
.login-block button {\
  width: 100%;\
  height: 50px;\
  box-sizing: border-box;\
  border-radius: 5px;\
  font-size: 16px;\
  outline: none;\
}\
\
.login-block h1 {\
  text-align: center;\
  color: #000;\
  font-size: 22px;\
  text-transform: uppercase;\
  margin-top: 2px;\
  margin-bottom: 25px;\
}\
\
.login-block input {\
  border: 1px solid #ccc;\
  margin-bottom: 20px;\
  padding: 0 20px 0 15px;\
  cursor: text;\
}\
\
.login-block input:active,\
.login-block input:focus {\
  border: 1px solid #37f;\
}\
\
.login-block button {\
  border: 0;\
  background: #37f;\
  color: #fff;\
  font-weight: 700;\
  text-transform: uppercase;\
  cursor: pointer;\
  background: #37f;\
}\
\
.login-block button:hover {\
  background: #6397ff;\
}\
\
.main-block {\
  width: 98%;\
  background: #fff;\
  border-radius: 5px;\
  margin: 0 auto;\
  margin-bottom: 60px;\
}\
\
.footer {\
  position: fixed;\
  bottom: 0;\
  width: 100%;\
  background-color: #ff0;\
  display: inline-block;\
}\
\
.footer p {\
  margin-right: 15px;\
  text-align: right;\
  line-height: 50px;\
  width: auto;\
  float: right;\
  cursor: help;\
}\
\
.footer img {\
  float: right;\
  padding: 12.5px;\
  height: 25px;\
  cursor: help;\
}\
</style>";*/

static const String footer = "\
<div class='footer'>\
  <p>Version: Alpha 1.1</p>\
</div>";

static const String login = "\
<div class='login-block'>\
  <form action='/login' method='POST'>\
    <h1>BuzzerShowSystem</h1>\
    <input type='text' placeholder='Username' name='USERNAME' required=''>\
    <input type='password' value='' placeholder='Password' name='PASSWORD' required=''>\
    <button>Login</button>\
  </form>\
</div>";

void get_login_string(String *string, String msg) {
  *string = head + login_header + "<body>" + login + msg + footer + "</body>" + style + "</html>";
}

void get_basics_string(String *string, String quiz_type, String box1, String box2, String box3) {
  *string = head + main_header + "\
<body>\
  <div id='body'>\
    <div id='nav-bar' class='grid'>\
      <a id='game' href=''>Game</a>\
      <a class='active' id='configuration' href=''>Configuration</a>\
      <a class='active' id='basics' href=''>Basics</a>\
      <a id='actions' href='/actions'>Actions</a>\
      <a id='dmx' href='/dmx'>DMX</a>\
    </div>\
    <form action='/save' method='POST'>\
      <div id='content' class='grid'>\
        <div id='quiz_type'>\
          <fieldset>\
            <legend>Quiztype:</legend>\
            <div id='mar'>\
              <select name='quiz_type'>\
                <option value='standart' selected>Standart</option>\
                <option value='ko-quiz'>KO-Quiz</option>\
              </select>\
            </div>\
          </fieldset>\
        </div>\
        <div id='checkboxses'>\
          <fieldset>\
            <legend>Game Rules:</legend>\
            <div id='mar'>\
              <div id='boxes' class='grid'>\
                <p id='text1'>When a answer was wrong the others players are Activated by the next reset</p>\
                <input id='box1' type='checkbox' name='PlayerWrongNextPlayserbyReset' value='1'>\
                <p id='text2'>The too late players can see his delays on the diplay</p>\
                <input id='box2' type='checkbox' name='PlayersCanSeeDelays' value='1'>\
                <p id='text3'>The players can press multiple times, with sound(Not recomended)</p>\
                <input id='box3' type='checkbox' name='PlayersPressMultipleTimes' value='1' checked>\
              </div>\
            </div>\
          </fieldset>\
        </div>\
      </div>\
      <div id='save_discard' class='grid'>\
        <input id='discard' type='reset' value='Discard'>\
        <input id='save' type='submit' value='Save'>\
      </div>\
    </form>\
  </div>\
  <script>\
    const QuizType = '" + quiz_type + "';\
    const GameRules = {'box1':" + box1 + ", 'box2':" + box2 + ", 'box3':" + box3 + "};\
\
    document.getElementsByName('quiz_type')[0].value = QuizType;\
\
    for (i in GameRules) {\
      document.getElementById(i).checked = GameRules[i];\
    }\
  </script>\
  " + disconnect + footer + "</body>" + style + "</html>";
}

void get_dmx_string(String *string, String NOL, String SC, String CPL, String brightness, String red, String green, String blue, String white) {
  *string = head + main_header + "\
<body>\
  <div id='body'>\
    <div id='nav-bar' class='grid'>\
      <a id='game' href=''>Game</a>\
      <a class='active' id='configuration' href=''>Configuration</a>\
      <a id='basics' href='/basics'>Basics</a>\
      <a id='actions' href='/actions'>Actions</a>\
      <a class='active' id='dmx' href=''>DMX</a>\
    </div>\
    <form action='/save' method='POST'>\
      <div id='content' class='grid'>\
        <div id='lights'>\
          <fieldset>\
            <legend>Lights: </legend>\
            <div id='mar'>\
              <div id='boxes' class='grid'>\
                <p id='text1'>Number of Lights</p>\
                <input id='box1' type='number' name='NumberOfLights' value='1'>\
                <p id='text2'>Start Channel</p>\
                <input id='box2' type='number' name='StartChannel' value='2'>\
                <p id='text3'>Channel per Light</p>\
                <input id='box3' type='number' name='ChannelPerLight' value='3'>\
                <p id='ch_pos'>Channel Position</p>\
                <div id='ch_pos_grid' class='grid'>\
                  <p class='bold'>B</p>\
                  <p class='bold'>R</p>\
                  <p class='bold'>G</p>\
                  <p class='bold'>B</p>\
                  <p class='bold'>W</p>\
                  <input type='number' name='Brightness' value='1'>\
                  <input type='number' name='Red' value='2'>\
                  <input type='number' name='Green' value='3'>\
                  <input type='number' name='Blue' value='4'>\
                  <input type='number' name='White' value='5'>\
                  <P>Brightness</P>\
                  <P>Red</P>\
                  <P>Green</P>\
                  <P>Blue</P>\
                  <P>White</P>\
                </div>\
              </div>\
            </div>\
          </fieldset>\
        </div>\
        <div id='test_dmx'>\
          <input id='button' type='submit' value='Test DMX'>\
        </div>\
      </div>\
      <div id='save_discard' class='grid'>\
        <input id='discard' type='reset' value='Discard'>\
        <input id='save' type='submit' value='Save'>\
      </div>\
    </form>\
  </div>\
  <script>\
    const Lights = {'NumberOfLights':'" + NOL + "', 'StartChannel':'" + SC + "', 'ChannelPerLight':'" + CPL + "'};\
    const ChannelPosition = {'Brightness':'" + brightness + "', 'Red':'" + red + "', 'Green':'" + green + "', 'Blue':'" + blue + "', 'White':'" + white + "'};\
\
    function ChangeValues (values) {\
      for (i in values) {\
        document.getElementsByName(i)[0].value = values[i];\
      }\
    }\
    ChangeValues(Lights); ChangeValues(ChannelPosition);\
  </script>\
  " + disconnect + footer + "</body>" + style + "</html>";
}

void get_action_string(String *string, String PPC, String OPC, String BPS, String PBBUK, String RPPC, String ROPC, String RAS, String RABUK, String WPPC, String WOPC, String WAS, String WABUK, String SColor, String DPC, String RBUK) {
  *string = head + main_header + "\
<body>\
  <div id='body'>\
  <div id='nav-bar' class='grid'>\
  <a id='game' href=''>Game</a>\
  <a class='active' id='configuration' href=''>Configuration</a>\
  <a id='basics' href='/basics'>Basics</a>\
  <a class='active' id='actions' href=''>Actions</a>\
  <a id='dmx' href='/dmx'>DMX</a>\
  </div>\
    <form action='/save' method='POST'>\
      <div id='content'>\
        <div id='buzzer_pressed'>\
          <fieldset>\
            <legend>Buzzer pressed:</legend>\
            <div id='mar'>\
              <div id='boxes' class='grid'>\
                <p>Pressed Player</p>\
                <input type='color' name='PressedPlayerColor' value='#0000FF'>\
                <p>Other Players too late</p>\
                <input type='color' name='OtherPlayersColor' value='#FFFF00'>\
                <select name='BuzzerPressedSound'>\
                  <option value='-1'>OFF</option>\
                  <option value='0' selected>Random</option>\
                  <option value='1'>Buzzer Pressed Sound 1</option>\
                  <option value='2'>Buzzer Pressed Sound 2</option>\
                  <option value='3'>Buzzer Pressed Sound 3</option>\
                  <option value='4'>Buzzer Pressed Sound 4</option>\
                  <option value='5'>Buzzer Pressed Sound 5</option>\
                  <option value='6'>Negative Buzzer Pressed Sound</option>\
                  <option value='7'>Negative Got Talent Buzzer</option>\
                  <option value='8'>Soft Buzzer Pressed Sound</option>\
                  <option value='9'>The Voice Buzzer</option>\
                  <option value='10'>TV Total Buzzer</option>\
                  <option value='11'>Among US Buzzer</option>\
                  <option value='12'>Cannon</option>\
                  <option value='13'>Rotes Licht Grünes Licht Ansage</option>\
                </select>\
                <input type='submit' name='PlayBuzzerPressedSound' value='Play'>\
                <select name='PressedBuzzerBadUsbKey'>\
                  <option value='0' selected>none</option>\
                  <option value='0x20'>Space</option>\
                  <option value='0xC2'>Enter</option>\
                  <option value='0xB2'>Backspace</option>\
                  <option value='0xC3'>Escape</option>\
                  <option value='0xE2'>Mute Speaker</option>\
                  <option value='0xCD'>Play/Pause</option>\
                  <option value='0xB0'>Play</option>\
                  <option value='0xB1'>Pause</option>\
                  <option value='0xB5'>Next</option>\
                  <option value='0xB6'>Previous</option>\
                  <option value='0x50'>Left Arrow</option>\
                  <option value='0x4F'>Right Arrow</option>\
                  <option value='0x52'>Up Arrow</option>\
                  <option value='0x51'>Down Arrow</option>\
                  <option value='0x70'>p</option>\
                  <option value='0x72'>r</option>\
                  <option value='0x77'>w</option>\
                  <option value='0x78'>x</option>\
                </select>\
                <input type='submit' name='TestPressedBuzzerBadUsbKey' value='Test'>\
              </div>\
            </div>\
          </fieldset>\
        </div>\
        <div id='right_anwser'>\
          <fieldset>\
            <legend>Right Answer:</legend>\
            <div id='mar'>\
              <div id='boxes' class='grid'>\
                <p>Right pressed Player</p>\
                <input type='color' name='RightPressedPlayerColor' value='#00FF00'>\
                <p>Right other Players</p>\
                <input type='color' name='RightOtherPlayersColor' value='#00FF00'>\
                <select name='RightAnswerSound'>\
                <option value='-1'>OFF</option>\
                <option value='0' selected>Random</option>\
                <option value='1'>Right Sond 1</option>\
                <option value='2'>Right Sond 2</option>\
                <option value='3'>Right Sond 3</option>\
                <option value='4'>Right Sond 4</option>\
                <option value='5'>Right ding</option>\
                <option value='6'>Right Game Sound</option>\
                <option value='7'>Zelda Item</option>\
                <option value='8'>WWM login</option>\
                <option value='9'>Celebration</option>\
                <option value='10'>Anime Wow</option>\
                <option value='11'>Kids cheering</option>\
                <option value='12'>YEAHAA</option>\
                <option value='13'>ehm_richtig</option>\
                <option value='14'>Instant dance party</option>\
                <option value='15'>boomshakalaka</option>\
                <option value='16'>Da hamse recht</option>\
                <option value='17'>Ja natürlich</option>\
                <option value='18'>Grünes Licht mit Scan</option>\
                <option value='19'>Grünes Licht</option>\
                </select>\
                <input type='submit' name='PlayRightAnswerSound' value='Play'>\
                <select name='RightAnswerBadUsbKey'>\
                  <option value='0' selected>none</option>\
                  <option value='0x20'>Space</option>\
                  <option value='0xC2'>Enter</option>\
                  <option value='0xB2'>Backspace</option>\
                  <option value='0xC3'>Escape</option>\
                  <option value='0xE2'>Mute Speaker</option>\
                  <option value='0xCD'>Play/Pause</option>\
                  <option value='0xB0'>Play</option>\
                  <option value='0xB1'>Pause</option>\
                  <option value='0xB5'>Next</option>\
                  <option value='0xB6'>Previous</option>\
                  <option value='0x50'>Left Arrow</option>\
                  <option value='0x4F'>Right Arrow</option>\
                  <option value='0x52'>Up Arrow</option>\
                  <option value='0x51'>Down Arrow</option>\
                  <option value='0x70'>p</option>\
                  <option value='0x72'>r</option>\
                  <option value='0x77'>w</option>\
                  <option value='0x78'>x</option>\
                </select>\
                <input type='submit' name='TestRightAnswerBadUsbKey' value='Test'>\
              </div>\
            </div>\
          </fieldset>\
        </div>\
        <div id='wrong_anwser'>\
          <fieldset>\
            <legend>Wrong Answer:</legend>\
            <div id='mar'>\
              <div id='boxes' class='grid'>\
                <p>Wrong pressed Player</p>\
                <input type='color' name='WrongPressedPlayersColor' value='#FF0000'>\
                <p>Wrong other Players</p>\
                <input type='color' name='WrongOtherPlayersColor' value='#FF0000'>\
                <select name='WrongAnswerSound'>\
                <option value='-1'>OFF</option>\
                <option value='0'selected>Random</option>\
                <option value='1'>Hard Wrong Sound 1</option>\
                <option value='2'>Hard Wrong Sound 2</option>\
                <option value='3'>Hard Wrong Sound 3</option>\
                <option value='4'>Hard Wrong Sound 4</option>\
                <option value='5'>Low Wrong Sound</option>\
                <option value='6'>Wa Wa Wa</option>\
                <option value='7'>wrong-price-is-right</option>\
                <option value='8'>Wasted</option>\
                <option value='9'>Family-fortunes-wrong-buzzer</option>\
                <option value='10'>XP Error</option>\
                <option value='11'>Computer sagt nein</option>\
                <option value='12'>Falsche Entscheidung</option>\
                <option value='13'>kann es sein das du dumm bist</option>\
                <option value='14'>ne</option>\
                <option value='15'>Omg bist du lost</option>\
                <option value='16'>Trump Wrong</option>\
                <option value='17'>Wrong</option>\
                <option value='18'>wrong wrong wrong</option>\
                <option value='19'>WWM Lost</option>\
                <option value='20'>you could not be more wrong</option>\
                <option value='21'>deez nuts</option>\
                <option value='22'>Nichtskönner</option>\
                <option value='23'>Rotes Licht</option>\
                </select>\
                <input type='submit' name='PlayWrongAnswerSound' value='Play'>\
                <select name='WrongAnswerBadUsbKey'>\
                  <option value='0' selected>none</option>\
                  <option value='0x20'>Space</option>\
                  <option value='0xC2'>Enter</option>\
                  <option value='0xB2'>Backspace</option>\
                  <option value='0xC3'>Escape</option>\
                  <option value='0xE2'>Mute Speaker</option>\
                  <option value='0xCD'>Play/Pause</option>\
                  <option value='0xB0'>Play</option>\
                  <option value='0xB1'>Pause</option>\
                  <option value='0xB5'>Next</option>\
                  <option value='0xB6'>Previous</option>\
                  <option value='0x50'>Left Arrow</option>\
                  <option value='0x4F'>Right Arrow</option>\
                  <option value='0x52'>Up Arrow</option>\
                  <option value='0x51'>Down Arrow</option>\
                  <option value='0x70'>p</option>\
                  <option value='0x72'>r</option>\
                  <option value='0x77'>w</option>\
                  <option value='0x78'>x</option>\
                </select>\
                <input type='submit' name='TestWrongAnswerBadUsbKey' value='Test'>\
              </div>\
            </div>\
          </fieldset>\
        </div>\
        <div id='game_standby'>\
          <fieldset>\
            <legend>Standby:</legend>\
            <div id='mar'>\
              <div id='boxes' class='grid'>\
                <p>Standby</p>\
                <input type='color' name='StandbyColor' value='#000000'>\
                <p>Deactivated Players</p>\
                <input type='color' name='DeactivatedPlayersColor' value='#FF0000'>\
                <select name='ResetBadUsbKey'>\
                  <option value='0' selected>none</option>\
                  <option value='0x20'>Space</option>\
                  <option value='0xC2'>Enter</option>\
                  <option value='0xB2'>Backspace</option>\
                  <option value='0xC3'>Escape</option>\
                  <option value='0xE2'>Mute Speaker</option>\
                  <option value='0xCD'>Play/Pause</option>\
                  <option value='0xB0'>Play</option>\
                  <option value='0xB1'>Pause</option>\
                  <option value='0xB5'>Next</option>\
                  <option value='0xB6'>Previous</option>\
                  <option value='0x50'>Left Arrow</option>\
                  <option value='0x4F'>Right Arrow</option>\
                  <option value='0x52'>Up Arrow</option>\
                  <option value='0x51'>Down Arrow</option>\
                  <option value='0x70'>p</option>\
                  <option value='0x72'>r</option>\
                  <option value='0x77'>w</option>\
                  <option value='0x78'>x</option>\
                </select>\
                <input type='submit' name='TestResetBadUsbKey' value='Test'>\
              </div>\
            </div>\
          </fieldset>\
        </div>\
      </div>\
      <div id='save_discard'>\
        <input id='discard' type='reset' value='Discard'>\
        <input id='save' type='submit' value='Save'>\
      </div>\
    </form>\
  </div>\
  <script>\
    const BuzzerPressed = {'PressedPlayerColor':'" + PPC + "', 'OtherPlayersColor':'" + OPC + "', 'BuzzerPressedSound':'" + BPS + "', 'PressedBuzzerBadUsbKey':'" + PBBUK + "'};\
    const RightAnswer   = {'RightPressedPlayerColor':'" + RPPC + "', 'RightOtherPlayersColor':'" + ROPC + "', 'RightAnswerSound':'" + RAS + "', 'RightAnswerBadUsbKey':'" + RABUK + "'};\
    const WrongAnswer   = {'WrongPressedPlayersColor':'" + WPPC + "', 'WrongOtherPlayersColor':'" + WOPC + "', 'WrongAnswerSound':'" + WAS + "', 'WrongAnswerBadUsbKey':'" + WABUK + "'};\
    const Standby       = {'StandbyColor':'" + SColor + "', 'DeactivatedPlayersColor':'" + DPC + "', 'ResetBadUsbKey':'" + RBUK + "'};\
\
    function ChangeValues (values){\
      for (i in values) {\
        document.getElementsByName(i)[0].value = values[i];\
      }\
    }\
\
    ChangeValues(BuzzerPressed);\
    ChangeValues(RightAnswer);\
    ChangeValues(WrongAnswer);\
    ChangeValues(Standby);\
  </script>\
  " + disconnect + footer + "</body>" + style + "</html>";
}
