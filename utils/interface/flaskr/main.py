from flask import Flask
from flask import render_template
import pandas as pd

app = Flask(__name__)


@app.route('/<int:index>')
def create_list(index):
    data = pd.read_csv(
        'utils/interface/flaskr/static/data/travels.csv', delimiter=';')
    row = data.iloc[index]
    inter = eval(row['inter'])
    horaires_inter = eval(row['horaires_inter'])

    spots_list = []
    for i in range(len(inter)):
        arrival_time = horaires_inter[2*i]
        departure_time = horaires_inter[2*i+1]
        charging_duration = departure_time - arrival_time
        spot_item = f"Arriving at spot '{inter[i]}' at {arrival_time}, charging for '{charging_duration}', leaving at '{departure_time}'"
        spots_list.append(spot_item)

    return render_template('template.html', spots_list=spots_list)


if __name__ == '__main__':
    app.run()


@app.route("/status")
def hello_world():
    return "<p>Up and running!</p>"


if __name__ == "__main__":
    app.run(debug=True)
