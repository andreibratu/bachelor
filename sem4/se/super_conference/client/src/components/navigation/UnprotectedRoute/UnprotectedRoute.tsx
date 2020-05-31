import {RootState} from "../../../redux";
import {Redirect, Route} from "react-router";
import * as React from "react";
import {useSelector} from "react-redux";

export const UnprotectedRoute = ({component: Component, componentProps, ...args}) => {
    const jwt = useSelector((state: RootState) => state.auth.token);
    return (
        <Route
            {...args}
            render={(routeProps) => {
                if (!jwt) return <Component {...componentProps} {...routeProps}/>;
                else return <Redirect to={{
                    pathname: '/',
                    state: {from: routeProps.location}
                }}/>
            }}
        />
    );
};
