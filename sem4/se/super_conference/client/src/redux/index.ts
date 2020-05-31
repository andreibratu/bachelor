import {combineReducers} from "redux";
import conferenceReducer from './conference/conferenceReducer';
import proposalReducer from "./proposal/proposalReducer";
import userReducer from "./user/userReducer";
import authenticationReducer from "./auth/authenticationReducer";
import notificationReducer from "./notification/notificationReducer";
import {Conference, JWT, Proposal, Review, User} from "./entities";
import contextReducer from "./context/contextReducer";

// Manually define it in order to avoid circular imports
export type RootState = {
    conference: { conferences: Conference[] },
    proposal: { proposals: Proposal[], reviews: Review[] },
    notification: { notifications: Notification[] },
    user: { users: User[] },
    auth: {
        firstname: string,
        lastname: string,
        email: string,
        token: JWT
    },
    context: {
        currentProposal: Proposal | null
    }
}

export type RootStateGetter = () => RootState;

export default combineReducers({
    conference: conferenceReducer,
    proposal: proposalReducer,
    notification: notificationReducer,
    user: userReducer,
    auth: authenticationReducer,
    context: contextReducer
});
