#include "web.h"
#include "sys_run.h"
const char *ssid = "AIoT Lab 2G";
const char *password = "ptitlab@123";
WebServer server(80);

void webSetup()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi đã kết nối!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/setSpeed", handleSetSpeed);
  server.on("/data", handleData);
  server.begin();
  Serial.println("Web Server đã khởi động!");
}

void handleRoot()
{
  String html = "<html>\
  <head>\
      <title>Dieu khien dong co</title>\
      <script src='https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js'></script>\
  </head>\
  <body>\
      <h1>Dieu khien toc do dong co</h1>\
      <form id='pidForm' action='/setSpeed' method='GET'>\
          <!-- Nhap gia tri Kp -->\
          <label for='kp'>Nhap gia tri Kp: (" +
                String(pid_motor.kp) + ")</label>\
          <input type='number' id='kp' name='kp' step='0.01' value='" + String(pid_motor.kp) + "' required>\
          <br><br>\
          \
          <!-- Nhap gia tri Ki -->\
          <label for='ki'>Nhap gia tri Ki: (" +
                String(pid_motor.ki, 5) + ")</label>\
          <input type='number' id='ki' name='ki' step='0.00001' value='" + String(pid_motor.ki, 5) + "' required>\
          <br><br>\
          \
          <!-- Nhap gia tri Kd -->\
          <label for='kd'>Nhap gia tri Kd: (" +
                String(pid_motor.kd) + ")</label>\
          <input type='number' id='kd' name='kd' step='0.01' value='" + String(pid_motor.kd) + "' required>\
          <br><br>\
          \
          <p id='outInfo' class='info'>Out: " +
                String(pid_motor.output) + "</p>\
          <p id='angleInfo' class='info'>Angles: " +
                String(roll) + "</p>\
          <!-- Nut gui -->\
          <input type='submit' id='submitBtn' value='Send'>\
      </form>\
      <canvas id='canvas'></canvas>\
      <script>\
        document.addEventListener('keydown', function (event) {\
          if (event.key === 'Enter') {\
            event.preventDefault();\
            document.getElementById('pidForm').submit();\
          }\
        });\
      </script>\
      <script>\
          let scene=new THREE.Scene();\
          let camera=new THREE.PerspectiveCamera(75, window.innerWidth/window.innerHeight, 0.1, 1000);\
          let renderer=new THREE.WebGLRenderer({canvas:document.getElementById('canvas')});\
          renderer.setSize(window.innerWidth,window.innerHeight);\
          document.body.appendChild(renderer.domElement);\
          let geometry=new THREE.BoxGeometry(10,1,1);\
          let materials = new THREE.MeshBasicMaterial({ color: 0xff0000 });\
          let cube=new THREE.Mesh(geometry,materials);\
          scene.add(cube);\
          camera.position.z=5;\
          function animate(){\
              requestAnimationFrame(animate);\
              renderer.render(scene,camera);\
          }\
          animate();\
          async function getData(){\
            let response=await fetch('/data');\
            let data=await response.text();\
            let parts = data.split(':');\
            roll = parseFloat(parts[1]);\
            cube.rotation.z= (roll * 3.142 / 180);\
            document.getElementById('angleInfo').innerText = 'Angles: ' + roll.toFixed(2);\
          }\
          setInterval(getData, 100);\
      </script>\
  </body>\
  <body style='background-image: url('https://upload.wikimedia.org/wikipedia/vi/d/d0/Logo_PTIT_University.png'); background-size: cover; background-repeat: no-repeat;'>\
  </html>";

  server.send(200, "text/html", html);
}

void handleSetSpeed()
{
  if (server.hasArg("kp") || server.hasArg("ki") || server.hasArg("kd"))
  {
    Controller.run(0, 0);
    delay(4000);
    pid_motor.kp = server.arg("kp").toDouble();
    pid_motor.ki = server.arg("ki").toDouble();
    pid_motor.kd = server.arg("kd").toDouble();
    pid_motor.P = 0;
    pid_motor.I = 0;
    pid_motor.D = 0;
    server.send(200, "text/html",
        "<h1>Thong so da duoc cap nhat</h1>"
        "<a href='/' id='backLink'> Back </a>"
        "<script>"
        "document.addEventListener('keydown', function(event) {"
        "  if (event.key === 'Enter') {"
        "    window.location.href = '/';"
        "  }"
        "});"
        "</script>");
  } 
  else
  {
    server.send(400, "text/plain", "Thieu thong so!");
  }
}

void handleData()
{
  String message = "Roll:" + String(roll); 
  server.send(200, "text/plain", message);
}

void webHandle()
{
  server.handleClient();
}
