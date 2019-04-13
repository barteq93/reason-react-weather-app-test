open WeatherDecoder;

type state = {
    editText: string,
    city: string,
    status: string,
};

type action =
    | Change(string)
    | Submit
    | StatusFetched(string);

let initialState = {
    editText: "London",
    city: "London",
    status: "",
};

let reducer = (state, action) =>
    switch action {
    | Change(value) => { ...state, editText: value }
    | Submit => { ...state, city: state.editText }
    | StatusFetched(status) => { ...state, status }
};

let apiUrl = "https://api.openweathermap.org/data/2.5/weather?APPID=e783fee51b687f49f5c8d082afb7e36e&q=";

[@react.component]
let make = () => {
    let (state, dispatch) = React.useReducer(reducer, initialState);

    React.useEffect1(
        () => {
            Js.Promise.(
                Fetch.fetch(apiUrl ++ state.editText)
                |> then_(Fetch.Response.json)
                |> then_(json => {
                    Js.log(json);
                    json |> WeatherDecoder.Decode.decodeData
                        //  |> Js.log
                         |> (data => dispatch(StatusFetched(data.weather[0].main)))
                         |> resolve
                })
                |> catch(err =>{
                    Js.log(err);
                    Js.Promise.resolve();
                })
            )
            -> ignore;
            None;
        },
        [|state.city|]
    );

    let handleInputChange = event => dispatch(Change(ReactEvent.Form.target(event)##value));
    let handleButtonClick = _event => dispatch(Submit);

    <div>
        <div>
            <input type_="text" onChange=handleInputChange />
            <button onClick=handleButtonClick>{ReasonReact.string("Go!")}</button>
        </div>
        <WeatherStatus city=state.city status=state.status />    
    </div>
};
