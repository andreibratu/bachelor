// @ts-nocheck
import {User} from "../entities";
import {GET_USERS, REMOVE_USER, UPDATE_USER} from './userActions'

type UserState = { users: User[] };
type Action = { type: string, payload: object }

const initState: UserState = {
    users: [
        {
            email: "somecoolguy@gmail.com",
            firstname: 'Dorin',
            lastname: 'Popescu'
        },
        {
            email: 'reee@gmail.com',
            firstname: 'Xiaolin',
            lastname: 'Showdown'
        },
        {
            email: 'notnice@yahoo.com',
            firstname: 'Grumpy',
            lastname: 'Oldman'
        },
        {
            email: 'boomermail@hotmail.com',
            firstname: 'Lizaveta',
            lastname: 'Chierasim'
        },
        {
            email: 'metroboomin@hills.co',
            firstname: 'Connard',
            lastname: 'Gelard'
        },
        {
            email: 'bratuandrei0@gmail.com',
            firstname: 'Andrei',
            lastname: 'Bratu'
        },
        {
            email: 'financeguy@gmail.com',
            firstname: 'Lao',
            lastname: 'Gin'
        }
    ]
};

export default function (state: UserState = initState, action: Action) {
    let newState: UserState = {users: []};
    let {type, payload} = action;
    switch (type) {
        case REMOVE_USER: {
            newState = {...state};
            newState.users = newState.users.filter(u => u.email !== payload.email);
            break;
        }
        case GET_USERS: {
            newState = {...state};
            newState.users = payload.users;
            break;
        }
        case UPDATE_USER: {
            newState = {...state};
            newState.users = newState.users.map(u => u.email === payload.user.email ? payload.user : u);
            break;
        }
        default:
            return state;
    }
    return newState;
}
