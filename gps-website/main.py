from flask import Flask, render_template, request, redirect, url_for
import requests as webhook
import configparser

config = configparser.ConfigParser()

config.read("config.ini")
prod = config['PROD']

app=Flask(__name__) 


def notification_post(waypoint_count):
    webhook_url = prod['WEBSITE']

    response_data = {
        "waypoints": {
        "long0":"111.111", "lat0":"112.111",
        "long1":"113.111", "lat1":"114.111",
        "long2":"115.111", "lat2":"116.111",
        "long3":"117.111", "lat3":"118.111",
        "long4":"119.111", "lat4":"120.111",
        "long5":"121.111", "lat5":"122.111"
        },
        "waypoint_status":{ 
            "waypoint_count": waypoint_count,
            "waypoint_start": {
                "enabled": 0,
                "start": 0
            },
            "waypoint_end": {
                "enabled": 0,
                "end": 0
            }
        },
        "status": {
            "navigating": 1,
            "motor_stop": 0
        },
        "rth_status": {
            "enabled": 0,
            "home_waypoint":{
                "long": "000.000", "lat": "001.000"
            }
        }
    }

    return webhook.post(webhook_url, json=response_data)

@app.route("/", methods = ["POST", "GET"])
def root():
    waypoint_count = 0
    if request.method == 'POST':
        waypoint_count = request.form['waypoint_count']
        print(waypoint_count)
        notification_post(waypoint_count)
    
    return render_template('index.html', default_count = waypoint_count)

# @app.route("/home/", methods = ["POST", "GET"])
# def home(): 
#     return render_template('index.html')

# @app.route()

if __name__ == "__main__": 
    app.run(host="localhost", port=8080, debug=True)
