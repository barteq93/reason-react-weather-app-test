[@react.component]
let make = (~city, ~status) =>
    <div>
        <span>{ReasonReact.string(city ++ ": ")}</span>
        <span>{ReasonReact.string(status)}</span>
    </div>;
