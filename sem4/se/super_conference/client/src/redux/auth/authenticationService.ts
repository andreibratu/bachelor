import domain, {JWT, logRequestError} from "../entities";
import {LOGIN, LOGOUT, REGISTER} from "./authenticationActions";
import {Dispatch} from "redux";

type AuthResponse = { firstname: string, lastname: string, email: string, token: string }
const request = require('request-promise-native');

const authenticationService =
    {
        register: (firstname: string, lastname: string, email: string, password: string) =>
            (dispatch: Dispatch) => request({
                method: "POST",
                url: `${domain}/api/register/`,
                json: true,
                body: {
                    firstname: firstname,
                    lastname: lastname,
                    email: email,
                    password: password
                }
            })
                .then((response: { token: JWT }) => dispatch({
                    type: REGISTER,
                    payload: {
                        firstname: firstname,
                        lastname: lastname,
                        email: email,
                        token: response.token
                    }
                }))
                .catch(logRequestError)
        ,

        login: (email: string, password: string) => (dispatch: Dispatch) => request({
            method: 'POST',
            url: `${domain}/api/login`,
            json: true,
            body: {email: email, password: password}
        })
            .then((response: AuthResponse) => dispatch({
                type: LOGIN,
                payload: {
                    firstname: response.firstname,
                    lastname: response.lastname,
                    email: response.email,
                    token: response.token
                }
            }))
            .catch(logRequestError)
        ,

        logout: () => (dispatch: Dispatch) => {
            dispatch({type: LOGOUT})
        }
    };

export default authenticationService;
