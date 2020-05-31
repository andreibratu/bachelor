import {Conference, Proposal, Review} from "../entities";
import {
    RESET_CONTEXT_PROPOSAL,
    UPDATE_CONTEXT_CONFERENCE,
    UPDATE_CONTEXT_PROPOSAL,
    UPDATE_CONTEXT_REVIEW
} from "./contextActions";

type ContextState = {
    currentProposal: Proposal | null,
    currentReview: Review | null,
    currentConference: Conference | null,
}

type Action = {
    type: string, payload: {
        proposal: Proposal | null,
        review: Review | null,
        conference: Conference | null
    }
};

const initialState: ContextState = {
    currentProposal: null,
    currentReview: null,
    currentConference: null
};

export default function (state: ContextState = initialState, action: Action) {
    let newState = {...state};
    const {type, payload} = action;
    switch (type) {
        case UPDATE_CONTEXT_PROPOSAL:
            newState.currentProposal = payload.proposal;
            break;
        case UPDATE_CONTEXT_REVIEW:
            newState.currentReview = payload.review;
            break;
        case RESET_CONTEXT_PROPOSAL:
            newState.currentProposal = null;
            break;
        case UPDATE_CONTEXT_CONFERENCE:
            newState.currentConference = payload.conference;
            break;
        default:
            break;
    }
    return newState;
}
