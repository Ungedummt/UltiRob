#include "Arduino.h"
#include "RGB.h"

String html;
uint8_t current_page = 0;


byte buffer_x[10] = {};

rgb page[5][74] = {
                 {{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }},

                 {{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }},

                 {{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }},

                 {{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }},

                 {{ 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 },
                 { 0, 0, 0 }, { 0, 0, 0 },}
                };


String gen_js_array(uint8_t page_num) {
    String js_array = "['#";
    for (uint8_t i = 0; i < 73; i++) {
        js_array += rgb_to_hex_string(page[page_num][i]);
        js_array += "', '#";
    }
    js_array += rgb_to_hex_string(page[page_num][73]);
    js_array += "']";
    return js_array;
}

String gen_c_array(uint8_t page_num) {
    String c_array = "{";
    for (uint8_t i = 0; i < 74; i++) {
        for (uint8_t j = 0; j < 3; j++) {
            if (j == 0) {
                c_array += "{";
                c_array += String(page[page_num][i].red);
                c_array += ",";
            } else if (j == 1) {
                c_array += String(page[page_num][i].green);
                c_array += ",";
            } else {
                c_array += String(page[page_num][i].blue);
                c_array += "},";
            }
        }
    }
    c_array += "}";
    return c_array;
}

void update_html_string() {
    html = """<!DOCTYPE html>\
    <html lang='en'>\
      <head>\
        <title>Configuration</title>\
        <style>\
          * {\
            font-family: Ubuntu, Calibri, Noto Sans;\
            font-size: 19px;\
            margin: 0;\
            padding: 0;\
            cursor: default;\
            color: #000;\
          }\
          #body {\
            border-top-color: #37f;\
            border-top-style: solid;\
            border-top-width: 5px;\
            background: #fff;\
            border-radius: 5px;\
            width: 700px;\
            margin: 28px auto 78px;\
          }\
          body {\
            background-color: #add8e6;\
          }\
          a {\
            font-weight: 700;\
            border-radius: 5px;\
            border: none;\
            text-align: center;\
            text-decoration: none;\
            display: inline-block;\
            line-height: 50px;\
            font-size: 25px;\
            color: #000;\
          }\
          .grid {\
            display: grid;\
          }\
          #colorsetter_box {\
            grid-template-columns: auto auto;\
            grid-gap: 10px;\
            padding: 20px 20px 0;\
          }\
          #colorsetter_box a {\
            height: 100%;\
            width: 100%;\
          }\
          #colorsetter {\
            height: 100%;\
            width: 50%;\
            margin-left: 35%;\
          }\
          #content {\
            grid-gap: 10px;\
            padding: 20px 30px;\
          }\
          #content legend {\
            padding-left: 4px;\
            margin: 0 auto;\
            padding-right: 8px;\
            font-size: 21px;\
          }\
          #content fieldset {\
            border-radius: 5px;\
            border-width: 2px;\
            border-color: #37f;\
            border-style: solid;\
          }\
          #content input[type='color'] {\
            width: 3em;\
            height: 3em;\
          }\
          .content_div {\
            width: 3em;\
            height: 3em;\
          }\
          .content_div_special {\
            width: 3em;\
            height: 3.5em;\
          }\
          #content #mar {\
            display: block;\
            width: 95%;\
            margin: 10px auto 15px;\
          }\
          #boxes {\
            grid-template-columns: auto auto auto auto auto auto auto auto;\
            grid-gap: 10px;\
          }\
          #save_discard {\
            grid-template-columns: auto auto;\
            grid-gap: 10px;\
            padding: 0 20px 20px;\
          }\
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
          #save_discard #save {\
            background: green;\
          }\
          #save_discard #discard {\
            background: red;\
          }\
          .main-block {\
            width: 98%;\
            background: #fff;\
            border-radius: 5px;\
            margin: 0 auto;\
            margin-bottom: 60px;\
          }\
        </style>\
      </head>\
      <body>\
        <div id='body'>\
          <form action='/save' method='post'>\
            <div id='colorsetter_box' class='grid'>\
              <a>Page select</a>\
              <select id='page_setter' name='page_setter'>\
                <option value='1'>1</option>\
                <option value='2'>2</option>\
                <option value='3'>3</option>\
                <option value='4'>4</option>\
                <option value='5'>5</option>\
              </select>\
              <a>Color to set</a>\
              <input type='color' name='colorsetter' id='colorsetter' value='#000000'>\
            </div>\
            <div id='content' class='grid'>\
              <div id='lights'>\
                <fieldset>\
                  <legend>Lights:</legend>\
                  <div id='mar'>\
                    <div id='boxes' class='grid'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
    \
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <input type='color' id='neopx_0' name='neopx_0' value='#000000'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <input type='color' id='neopx_1' name='neopx_1' value='#000000'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
    \
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
                      <div class='content_div_special'></div>\
    \
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <input type='color' id='neopx_2' name='neopx_2' value='#000000'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <input type='color' id='neopx_3' name='neopx_3' value='#000000'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
    \
                      <input type='color' id='neopx_4' name='neopx_4' value='#000000'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <input type='color' id='neopx_5' name='neopx_5' value='#000000'>\
    \
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <input type='color' id='neopx_6' name='neopx_6' value='#000000'>\
                      <input type='color' id='neopx_7' name='neopx_7' value='#000000'>\
                      <input type='color' id='neopx_8' name='neopx_8' value='#000000'>\
                      <input type='color' id='neopx_9' name='neopx_9' value='#000000'>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
    \
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
                      <div class='content_div'></div>\
    \
                      <input type='color' id='neopx_10' name='neopx_10' value='#000000'>\
                      <input type='color' id='neopx_11' name='neopx_11' value='#000000'>\
                      <input type='color' id='neopx_12' name='neopx_12' value='#000000'>\
                      <input type='color' id='neopx_13' name='neopx_13' value='#000000'>\
                      <input type='color' id='neopx_14' name='neopx_14' value='#000000'>\
                      <input type='color' id='neopx_15' name='neopx_15' value='#000000'>\
                      <input type='color' id='neopx_16' name='neopx_16' value='#000000'>\
                      <input type='color' id='neopx_17' name='neopx_17' value='#000000'>\
                      <input type='color' id='neopx_18' name='neopx_18' value='#000000'>\
                      <input type='color' id='neopx_19' name='neopx_19' value='#000000'>\
                      <input type='color' id='neopx_20' name='neopx_20' value='#000000'>\
                      <input type='color' id='neopx_21' name='neopx_21' value='#000000'>\
                      <input type='color' id='neopx_22' name='neopx_22' value='#000000'>\
                      <input type='color' id='neopx_23' name='neopx_23' value='#000000'>\
                      <input type='color' id='neopx_24' name='neopx_24' value='#000000'>\
                      <input type='color' id='neopx_25' name='neopx_25' value='#000000'>\
                      <input type='color' id='neopx_26' name='neopx_26' value='#000000'>\
                      <input type='color' id='neopx_27' name='neopx_27' value='#000000'>\
                      <input type='color' id='neopx_28' name='neopx_28' value='#000000'>\
                      <input type='color' id='neopx_29' name='neopx_29' value='#000000'>\
                      <input type='color' id='neopx_30' name='neopx_30' value='#000000'>\
                      <input type='color' id='neopx_31' name='neopx_31' value='#000000'>\
                      <input type='color' id='neopx_32' name='neopx_32' value='#000000'>\
                      <input type='color' id='neopx_33' name='neopx_33' value='#000000'>\
                      <input type='color' id='neopx_34' name='neopx_34' value='#000000'>\
                      <input type='color' id='neopx_35' name='neopx_35' value='#000000'>\
                      <input type='color' id='neopx_36' name='neopx_36' value='#000000'>\
                      <input type='color' id='neopx_37' name='neopx_37' value='#000000'>\
                      <input type='color' id='neopx_38' name='neopx_38' value='#000000'>\
                      <input type='color' id='neopx_39' name='neopx_39' value='#000000'>\
                      <input type='color' id='neopx_40' name='neopx_40' value='#000000'>\
                      <input type='color' id='neopx_41' name='neopx_41' value='#000000'>\
                      <input type='color' id='neopx_42' name='neopx_42' value='#000000'>\
                      <input type='color' id='neopx_43' name='neopx_43' value='#000000'>\
                      <input type='color' id='neopx_44' name='neopx_44' value='#000000'>\
                      <input type='color' id='neopx_45' name='neopx_45' value='#000000'>\
                      <input type='color' id='neopx_46' name='neopx_46' value='#000000'>\
                      <input type='color' id='neopx_47' name='neopx_47' value='#000000'>\
                      <input type='color' id='neopx_48' name='neopx_48' value='#000000'>\
                      <input type='color' id='neopx_49' name='neopx_49' value='#000000'>\
                      <input type='color' id='neopx_50' name='neopx_50' value='#000000'>\
                      <input type='color' id='neopx_51' name='neopx_51' value='#000000'>\
                      <input type='color' id='neopx_52' name='neopx_52' value='#000000'>\
                      <input type='color' id='neopx_53' name='neopx_53' value='#000000'>\
                      <input type='color' id='neopx_54' name='neopx_54' value='#000000'>\
                      <input type='color' id='neopx_55' name='neopx_55' value='#000000'>\
                      <input type='color' id='neopx_56' name='neopx_56' value='#000000'>\
                      <input type='color' id='neopx_57' name='neopx_57' value='#000000'>\
                      <input type='color' id='neopx_58' name='neopx_58' value='#000000'>\
                      <input type='color' id='neopx_59' name='neopx_59' value='#000000'>\
                      <input type='color' id='neopx_60' name='neopx_60' value='#000000'>\
                      <input type='color' id='neopx_61' name='neopx_61' value='#000000'>\
                      <input type='color' id='neopx_62' name='neopx_62' value='#000000'>\
                      <input type='color' id='neopx_63' name='neopx_63' value='#000000'>\
                      <input type='color' id='neopx_64' name='neopx_64' value='#000000'>\
                      <input type='color' id='neopx_65' name='neopx_65' value='#000000'>\
                      <input type='color' id='neopx_66' name='neopx_66' value='#000000'>\
                      <input type='color' id='neopx_67' name='neopx_67' value='#000000'>\
                      <input type='color' id='neopx_68' name='neopx_68' value='#000000'>\
                      <input type='color' id='neopx_69' name='neopx_69' value='#000000'>\
                      <input type='color' id='neopx_70' name='neopx_70' value='#000000'>\
                      <input type='color' id='neopx_71' name='neopx_71' value='#000000'>\
                      <input type='color' id='neopx_72' name='neopx_72' value='#000000'>\
                      <input type='color' id='neopx_73' name='neopx_73' value='#000000'>\
                    </div>\
                  </div>\
                </fieldset>\
              </div>\
            </div>\
            <div id='save_discard' class='grid'>\
              <input id='discard' type='reset' value='Discard' />\
              <input id='save' type='submit' value='Save' />\
            </div>\
          </form>\
        </div>\
        <script>\
          var page_1 = """;
    html += gen_js_array(0);
    html += """; var page_2 = """;
    html += gen_js_array(1);
    html += """; var page_3 = """;
    html += gen_js_array(2);
    html += """; var page_4 = """;
    html += gen_js_array(3);
    html += """; var page_5 = """;
    html += gen_js_array(4);
    html += """; var current_page = """;
    html += current_page;
    html += """;\
          function get_page(page_num) {\
            return window['page_' + page_num.toString()];\
          }\
    \
          function set_page(page_num) {\
            var page_var = get_page(page_num);\
            for (let i = 0; i < 74; i++) {\
              var neopx = document.getElementById('neopx_' + i.toString());\
              neopx.value = page_var[i];\
            }\
          }\
    \
          function set_page_combo_box(page_num) {\
            document.getElementById('page_setter').value = page_num.toString();\
          }\
    \
          set_page(current_page + 1);\
          set_page_combo_box(current_page + 1);\
    \
          var page_setter = document.getElementById('page_setter');\
          page_setter.addEventListener('change', function(event) {\
            var pg_setter = event.target;\
            var page_num = pg_setter.options[pg_setter.selectedIndex].value;\
            set_page(page_num);\
            current_page = page_num;\
          });\
    \
    \
          for (let i = 0; i < 74; i++) {\
            var neopx = document.getElementById('neopx_' + i.toString());\
            neopx.addEventListener('click', function(event) {\
              console.log('neopx_' + i);\
              event.preventDefault();\
              var color = document.getElementById('colorsetter').value;\
              console.log(color);\
              event.target.value = color;\
            });\
          }\
        </script>\
      </body>\
    </html>\
    """;
}
