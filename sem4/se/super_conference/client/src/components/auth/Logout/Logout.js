import React from 'react';
import './Logout.css';
import {Redirect} from "react-router";
import authenticationService from "../../../redux/auth/authenticationService";
import {useDispatch} from "react-redux";

const Logout = (props) => {
    let dispatch = useDispatch();

    dispatch(authenticationService.logout());

    return <Redirect to={{pathname: "/login", state: {from: props.location}}}/>
};

Logout.propTypes = {};

Logout.defaultProps = {};

export default Logout;
