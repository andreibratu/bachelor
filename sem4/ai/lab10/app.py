import dash
import dash_core_components as dcc
import dash_html_components as html

from service import control

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']
# Nota bene: Dash will automatically serve all files found in the `assets` folder

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div(
    className="container",
    children=[
        html.H1('Furnace Control'),
        dcc.Slider(
            id='temperature-slider',
            min=20,
            max=120,
            step=1,
            value=70,
            marks={x: str(x) for x in range(20, 121, 10)}),
        dcc.Slider(
            id='capacity-slider',
            min=0,
            max=10,
            step=1,
            value=10,
            marks={x: str(x) for x in range(11)}),
        html.Div(id='power-result'),
        dcc.Slider(
            id='power-slider',
            min=0,
            max=20,
            step=0.1,
            marks={x: str(x) for x in range(0, 21, 4)},
            disabled=True
        )
    ]
)


@app.callback(
    dash.dependencies.Output('power-result', 'children'),
    [
        dash.dependencies.Input('temperature-slider', 'value'),
        dash.dependencies.Input('capacity-slider', 'value')
    ]
)
def update_output(temperature: int, capacity: int):
    power_level = control(temperature, capacity)
    power_level = round(power_level, 3)
    return f'For {temperature} temperature and {capacity} capacity, power is {power_level}'


@app.callback(
    dash.dependencies.Output('power-slider', 'value'),
    [
        dash.dependencies.Input('temperature-slider', 'value'),
        dash.dependencies.Input('capacity-slider', 'value')
    ]
)
def update_output(temperature: int, capacity: int):
    power_level = control(temperature, capacity)
    return power_level


if __name__ == '__main__':
    app.run_server(debug=True)
