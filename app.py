from flask import Flask, render_template, request, redirect
import requests
import sys
import os
app = Flask(__name__)

@app.route('/')
def index():
    return redirect('/menu')

@app.route('/menu')
def home():
    return render_template('menu.html')

@app.route('/search', methods=['POST'])
def search():
    if request.method == 'POST':
        departure = request.form['departure']
        arrival = request.form['arrival']
        car = request.form['car']
        heure_depart = request.form['heure_depart']
        max_charging_time = request.form['max_charging_time']
        max_waiting_time = request.form['max_waiting_time']
        battery_minimum = request.form['battery_minimum']
        return redirect('/search/' + departure + '/' + arrival + '/' + car + '/' + heure_depart + '/' + max_charging_time + '/' + max_waiting_time + '/' + battery_minimum)
    
@app.route('/search/<departure>/<arrival>/<car>/<heure_depart>/<max_charging_time>/<max_waiting_time>/<battery_minimum>')
def search_result(departure, arrival, car, heure_depart, max_charging_time, max_waiting_time, battery_minimum):
    """
    os.system("command")
    """
    return render_template('search.html', departure=departure, arrival=arrival, car=car, heure_depart=heure_depart, max_charging_time=max_charging_time, max_waiting_time=max_waiting_time, battery_minimum=battery_minimum)


if __name__ == '__main__':
    app.run(debug=1, use_reloader=True, host='0.0.0.0', port='5451')