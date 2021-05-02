import React from "react";
import ReactDOM from "react-dom";
import "./index.css";
import App from "./App";
import reportWebVitals from "./reportWebVitals";
import { BrowserRouter, Route } from "react-router-dom";
import LCS from "./Pages/LCS";
import SCS from "./Pages/SCS";
import ED from "./Pages/ED";
import LIS from "./Pages/LIS";
import MCM from "./Pages/MCM";
import KP from "./Pages/KP";
import RC from "./Pages/RC";
import PP from "./Pages/PP";
import CCP from "./Pages/CCP";
import WBP from "./Pages/WBP";

ReactDOM.render(
  <React.StrictMode>
    <BrowserRouter>
      <switch>
        <Route exact path="/" component={() => <App />} />
        <Route exact path="/LCS" component={() => <LCS />} />
        <Route exact path="/SCS" component={() => <SCS />} />
        <Route exact path="/LIS" component={() => <LIS />} />
        <Route exact path="/ED" component={() => <ED />} />
        <Route exact path="/MCM" component={() => <MCM />} />
        <Route exact path="/KP" component={() => <KP />} />
        <Route exact path="/PP" component={() => <PP />} />
        <Route exact path="/RC" component={() => <RC />} />
        <Route exact path="/CCP" component={() => <CCP />} />
        <Route exact path="/WBP" component={() => <WBP />} />
      </switch>
    </BrowserRouter>
  </React.StrictMode>,
  document.getElementById("root")
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();
