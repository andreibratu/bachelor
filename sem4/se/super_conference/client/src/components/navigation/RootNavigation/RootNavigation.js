import React from 'react';
import './RootNavigation.css';
import {UnprotectedRoute} from "../UnprotectedRoute/UnprotectedRoute";
import AuthForm from "../../auth/AuthForm/AuthForm";
import Dashboard from "../../generic/Dashboard/Dashboard";
import {Redirect, Route, Switch} from "react-router-dom";
import Logout from "../../auth/Logout/Logout";
import NotFound from "../NotFound/NotFound";

const RootNavigation = () =>
    <div className="RootNavigation">
        <Switch>
            <UnprotectedRoute path="/login" component={AuthForm} componentProps={{isRegister: false}}/>

            <UnprotectedRoute path="/register" component={AuthForm} componentProps={{isRegister: true}}/>

            <UnprotectedRoute path={'/dashboard'} component={Dashboard}/>

            <Route path={'/logout'} component={Logout}/>

            <Route exact path={""} render={() => <Redirect to={'/dashboard'}/>}/>

            <Route path={'*'} render={() => <NotFound/>}/>
        </Switch>
    </div>
;

RootNavigation.propTypes = {};

RootNavigation.defaultProps = {};

export default RootNavigation;
