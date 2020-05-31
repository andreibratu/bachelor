import domain, {buildAuthHeader, logRequestError, User} from '../entities';
import {GET_USERS, REMOVE_USER, UPDATE_USER} from "./userActions";
import {Dispatch} from "redux";
import {RootStateGetter} from "../index";

const request = require('request-promise-native');

const userService = {
    removeUser: (email: string) => (dispatch: Dispatch, getState: RootStateGetter) => request({
        method: "DELETE",
        url: `${domain}/api/users?email=${email}`,
        headers: buildAuthHeader(getState())
    })
        .then(_ => dispatch({
            type: REMOVE_USER,
            payload: {user: email}
        }))
        .catch(logRequestError)
    ,

    getUsers: () => (dispatch: Dispatch, getState: RootStateGetter) => request({
        method: "GET",
        url: `${domain}/api/users/`,
        headers: buildAuthHeader(getState())
    })
        .then((response: User[]) => dispatch({
            type: GET_USERS,
            payload: {users: response}
        }))
        .catch(logRequestError)
    ,

    updateUser: (updatedUser: User) => (dispatch: Dispatch, getState: RootStateGetter) => request({
        method: 'PUT',
        url: `${domain}/api/users`,
        json: true,
        headers: buildAuthHeader(getState()),
        body: {...updatedUser}
    })
        .then(_ => dispatch({
            type: UPDATE_USER,
            payload: {user: updatedUser}
        }))
        .catch(logRequestError)
};

export default userService;


