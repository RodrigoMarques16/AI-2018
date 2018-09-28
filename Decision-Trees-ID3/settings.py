DEBUG = False

problems = {
    "restaurant":{
        'file':'./data/restaurant.csv',
        'outfile':'./output/restaurant_out.txt',
        'testfile':'./tests/restaurant_test.csv',
        'continuous':[],
        'target':'Class'
    },
    "weather":{
        'file':'./data/weather.csv',
        'outfile':'./output/weather_out.txt',
        'testfile':'./tests/weather_test.csv',
        'continuous':['Temp', 'Humidity'],
        'size':4,
        'target':'Play'
    },
    "iris":{
        'file':'./data/iris.csv',
        'outfile':'./output/iris_out.txt',
        'testfile':'./tests/iris_test.csv',
        'continuous':['petalwidth', 'petallength', 'sepalwidth', 'sepallength'],
        'size':5,
        'target':'class'
    }
}
