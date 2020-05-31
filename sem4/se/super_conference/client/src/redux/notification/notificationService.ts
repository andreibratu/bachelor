import domain, {buildAuthHeader, logRequestError} from "../entities";
import {GET_NOTIFICATIONS, READ_NOTIFICATION} from "./notificationActions";
import {Dispatch} from "redux";
import {RootStateGetter} from "../index";

const request = require('request-promise-native');

export const notificationService =
    {
        getNotifications: () => (dispatch: Dispatch, getState: RootStateGetter) => request({
            method: 'GET',
            url: `${domain}/api/notifications`,
            headers: buildAuthHeader(getState())
        })
            .then((response: Notification[]) => dispatch({
                type: GET_NOTIFICATIONS,
                notifications: response
            }))
            .catch(logRequestError)
        ,

        readNotification: (notificationId: number) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: 'PATCH',
                url: `${domain}/api/notifications/${notificationId}`,
                headers: buildAuthHeader(getState())
            })
                .then(_ => dispatch({
                    type: READ_NOTIFICATION,
                    notificationId: notificationId
                }))
                .catch(logRequestError)
};
