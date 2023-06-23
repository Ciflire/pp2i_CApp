from flask import Flask, render_template, request, redirect
from utils.heatmap import heatmap
import requests
import sys
import os
from random import *
app = Flask(__name__)


# read the file path and return the string stored in the fist line
def read_response_file(path):
    file = open(path, "r")
    response = file.read().strip()
    file.close()
    return response


def read_data_file(path):
    file = open(path, "r")
    list = file.read().split("\n")
    file.close()
    response = eval(list[-2])
    return response


@app.route('/')
def index():
    return redirect('/home')


@app.route('/home')
def home():
    return render_template('home.html')


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
    os.system("./bin/app " + car + " "+departure+" "+heure_depart+" " +
              arrival+" "+battery_minimum+" "+max_charging_time+" "+max_waiting_time)
    link = read_response_file("data/response_link.txt")
    list_borne = read_data_file("data/response_borne.txt")
    list_horaires = read_data_file("data/response_horaires.txt")
    return render_template('search.html', departure=departure, arrival=arrival, car=car, heure_depart=heure_depart, max_charging_time=max_charging_time, max_waiting_time=max_waiting_time, battery_minimum=battery_minimum, link=link, list_borne=list_borne, list_horaires=list_horaires)


@app.route('/simulation', methods=['GET'])
def simulation():
    return render_template('simul.html', nb_cars=-1)


@app.route('/simul', methods=['POST'])
def simul():
    if request.method == 'POST':
        nb_cars = request.form['nb_cars']
        seed = randint(0, 1000000)
        return redirect('/simul/' + str(nb_cars) + '/' + str(seed))


@app.route('/simul/<nb_cars>/<seed>')
def simul_result(nb_cars, seed):
    os.system("./bin/app " + str(nb_cars) + " "+str(seed))
    heatmap()
    return render_template('simul.html', nb_cars=nb_cars)


@app.route('/reset', methods=['GET'])
def reset():
    # reset the link data file
    f = open("data/response_link.txt", "w")
    f.write("")
    f.close()
    # reset the horaires data file
    f = open("data/response_horaires.txt", "w")
    f.write("")
    f.close()
    # reset the borne data file
    f = open("data/response_borne.txt", "w")
    f.write("")
    f.close()
    # reset the pdc data file
    f = open("data/response_pdc.txt", "w")
    reset = ""
    for i in range(64501):
        reset += "[]\n"
    print(reset)
    f.write(reset)
    f.close()
    # reset the max pdc counter
    f = open("data/nb_max_pdc.txt", "w")
    f.write("0\n")
    f.close()
    return redirect('/home')


if __name__ == '__main__':
    app.run(debug=1, use_reloader=True, host='0.0.0.0', port='5451')
