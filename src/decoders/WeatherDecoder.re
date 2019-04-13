type coordType = {
    lon: float,
    lat: float,
};

type weather = {
    id: int,
    main: string,
    description: string,
    icon: string,
};

type main = {
    temp: float,
    pressure: int,
    humidity: int,
    temp_min: float,
    temp_max: float,
};

type wind = {
    speed: float,
    deg: int,
};

type clouds = {
    all: int,
};

type sys = {
    [@bs.as "type"] type_: int,
    id: int,
    message: float,
    country: string,
    sunrise: int,
    sunset: int,
};

type weatherResponse = {
    coord: coordType,
    weather: array(weather),
    base: string,
    main: main,
    visibility: int,
    wind: wind,
    clouds: clouds,
    dt: int,
    sys: sys,
    id: int,
    name: string,
    cod: int,
};

module Decode = {
    let decodeCoord = json: coordType => Json.Decode.{
        lon: json |> field("lon", float),
        lat: json |> field("lat", float),
    };

    let decodeWeather = json: weather => Json.Decode.{
        id: json |> field("id", int),
        main: json |> field("main", string),
        description: json |> field("description", string),
        icon: json |> field("icon", string),
    };

    let decodeMain = json: main => Json.Decode.{
        temp: json |> field("temp", float),
        pressure: json |> field("pressure", int),
        humidity: json |> field("humidity", int),
        temp_min: json |> field("temp_min", float),
        temp_max: json |> field("temp_max", float),
    };

    let decodeWind = json: wind => Json.Decode.{
        speed: json |> field("speed", float),
        deg: json |> field("deg", int),
    };

    let decodeClouds = json: clouds => Json.Decode.{
        all: json |> field("all", int),
    };

    let decodeSys = json: sys => Json.Decode.{
        type_: json |> field("type", int),
        id: json |> field("id", int),
        message: json |> field("message", float),
        country: json |> field("country", string),
        sunrise: json |> field("sunrise", int),
        sunset: json |> field("sunset", int),
    };

    let decodeData = json: weatherResponse => Json.Decode.{
        coord: json |> field("coord", decodeCoord),
        weather: json |> field("weather", array(decodeWeather)),
        base: json |> field("base", string),
        main: json |> field("main", decodeMain),
        visibility: json |> field("visibility", int),
        wind: json |> field("wind", decodeWind),
        clouds: json |> field("clouds", decodeClouds),
        dt: json |> field("dt", int),
        sys: json |> field("sys", decodeSys),
        id: json |> field("id", int),
        name: json |> field("name", string),
        cod: json |> field("cod", int),
    };
};
