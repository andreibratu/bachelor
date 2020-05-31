// @ts-nocheck
import {Notification} from "../entities";
import {GET_NOTIFICATIONS, READ_NOTIFICATION} from "./notificationActions";

type NotificationState = { notifications: Notification[] };
type Action = { type: string, payload: object }

export default function (state: NotificationState = {notifications: []}, action: Action) {
    let newState: NotificationState = {notifications: []};
    const {type, payload} = action;
    switch (type) {
        case GET_NOTIFICATIONS: {
            newState = {...state};
            newState.notifications = payload.notifications;
            break;
        }
        case READ_NOTIFICATION: {
            newState = {...state};
            const read: Notification = newState.notifications.find(n => n.id === payload.notificationId);
            read.read = true;
            newState.notifications = newState.notifications.map(n => n.id === id ? read : n);
            break;
        }
        default:
            return state;
    }
    return newState;
}
