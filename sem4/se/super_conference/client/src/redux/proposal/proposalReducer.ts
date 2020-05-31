import {Email, Proposal, Review} from "../entities";
import {
    ADD_BID,
    ADD_PROPOSAL,
    ADD_REVIEW,
    ADD_SH,
    FETCH_BIDDERS,
    FETCH_REVIEWS,
    GET_PROPOSALS,
    REMOVE_PROPOSAL,
    UPDATE_REVIEW
} from "./proposalActions";


type ProposalState = { proposals: Proposal[], reviews: Review[] };

const initialState: ProposalState =
    {
        proposals: [
            {
                id: 0,
                conferenceId: 0,
                proposalName: 'Super Cool',
                abstract: 'A really long ass proposal abstract I wish I had just stayed in bed.',
                topics: ['ML', 'Economy'],
                keywords: ['Neural Networks', 'Stocks', 'Prediction'],
                bidders: ['financeguy@gmail.com', 'bratuandrei0@gmail.com'],
                coAuthors: [],
                filePath: '',
                author: 'financeguy@gmail.com',
                reviewers: ['somecoolguy@gmail.com', 'bratuandrei0@gmail.com'],
                secondHandReviewer: null
            }
        ],
        reviews: [{
            id: 0,
            proposalId: 0,
            reviewer: "bratuandrei0@gmail.com",
            justification: 'Nice nice really nice',
            grade: 2
        }]
    };

function getProposal(oldState: ProposalState, proposalId: number) {
    return {...oldState.proposals.find(p => p.id === proposalId)};
}

function updateProposal(oldState: ProposalState, proposal: Proposal): ProposalState {
    const newState = {...oldState};
    newState.proposals = oldState.proposals.map(p => p.id === proposal.id ? proposal : p);
    return newState
}

type Action = {
    type: string,
    payload: {
        proposal: Proposal,
        proposals: Proposal[],
        review: Review,
        proposalId: number,
        bidder: Email,
        bidders: Email[],
        reviews: Review[],
        shEmail: Email
    }
}

export default (state: ProposalState = initialState, action: Action) => {
    let newState: ProposalState = {...state};
    let {type, payload} = action;
    let proposal: Proposal;
    switch (type) {
        case ADD_PROPOSAL: {
            // @ts-ignore
            newState.proposals.push(payload.proposal);
            break;
        }
        case REMOVE_PROPOSAL: {
            newState.proposals = newState.proposals.filter(p => p.id !== payload.proposalId);
            break;
        }
        case GET_PROPOSALS: {
            // @ts-ignore
            newState.proposals = proposals;
            break;
        }
        case ADD_REVIEW: {
            newState.reviews.push(payload.review);
            break;
        }
        case FETCH_REVIEWS: {
            newState.reviews = payload.reviews;
            break;
        }
        case ADD_BID: {
            // @ts-ignore
            proposal = getProposal(state, payload.proposalId);
            // @ts-ignore
            proposal.bidders.push(payload.bidder);
            newState = updateProposal(state, proposal);
            break;
        }
        case FETCH_BIDDERS:
            // @ts-ignore
            proposal = getProposal(state, payload.proposalId);
            // @ts-ignore
            proposal.bidders = payload.bidders;
            newState = updateProposal(state, proposal);
            break;
        case ADD_SH:
            // @ts-ignore
            proposal = getProposal(state, payload.proposalId);
            // @ts-ignore
            proposal.secondHandReviewer = payload.shEmail;
            newState = updateProposal(state, proposal);
            break;
        case UPDATE_REVIEW:
            newState.reviews = newState.reviews.map(r => r.id === payload.review.id ?
                payload.review : r
            );
            break;
        default:
            break;
    }
    return newState;
}
