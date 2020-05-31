import domain, {buildAuthHeader, logRequestError, Proposal, Review} from '../entities';
import {
    ADD_BID,
    ADD_PROPOSAL,
    ADD_REVIEW,
    ADD_SH,
    FETCH_REVIEWS,
    GET_PROPOSALS,
    REMOVE_BID,
    REMOVE_PROPOSAL,
    UPDATE_REVIEW
} from "./proposalActions";
import {RootStateGetter} from "../index";
import {Dispatch} from "redux";

const request = require('request-promise-native');

const proposalService =
    {
        // File expected as base64 string
        addProposal: (conferenceId: number, proposal: Proposal, proposalFile: string) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "POST",
                url: `${domain}/api/conferences/${conferenceId}/proposals/`,
                json: true,
                headers: buildAuthHeader(getState()),
                body: {
                    author: proposal.author,
                    proposalName: proposal.proposalName,
                    file: proposalFile,
                    abstract: proposal.abstract,
                    topics: proposal.topics,
                    keywords: proposal.keywords,
                    coAuthors: proposal.coAuthors,
                    conferenceId: conferenceId
                }
            })
                .then((response: Proposal) => dispatch({
                    type: ADD_PROPOSAL,
                    payload: {proposal: response}
                }))
                .catch(logRequestError)
        ,

        // File expected as base64 string
        updateProposal: (conferenceId: number, proposal: Proposal, proposalFile: string) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "POST",
                url: `${domain}/api/conferences/${conferenceId}/proposals/`,
                json: true,
                headers: buildAuthHeader(getState()),
                body: {
                    conferenceId: proposal.conferenceId,
                    author: proposal.author,
                    proposalName: proposal.proposalName,
                    file: proposalFile,
                    abstract: proposal.abstract,
                    topics: proposal.topics,
                    keywords: proposal.keywords,
                    coAuthors: proposal.coAuthors,
                }
            })
                .then((response: Proposal) => dispatch({
                    type: ADD_PROPOSAL,
                    payload: {proposal: response}
                }))
                .catch(logRequestError)
        ,

        removeProposal: (conferenceId: number, proposalId: number) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "DELETE",
                headers: buildAuthHeader(getState()),
                url: `${domain}/api/conferences/${conferenceId}/proposals?id=${proposalId}`,
            })
                .then(_ => dispatch({
                    type: REMOVE_PROPOSAL,
                    payload: {proposalId: proposalId}
                }))
                .catch(logRequestError)
        ,

        getProposals: (conferenceId: number) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "GET",
                headers: buildAuthHeader(getState()),
                url: `${domain}/api/conferences/${conferenceId}/proposals`
            })
                .then((response: Proposal[]) => dispatch({
                    type: GET_PROPOSALS,
                    payload: {proposals: response}
                }))
                .catch(logRequestError)
        ,

        addReview: (conferenceId: number, proposalId: number, review: Review) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "POST",
                url: `${domain}/api/conferences/${conferenceId}/proposals/${proposalId}/reviews`,
                json: true,
                headers: buildAuthHeader(getState()),
                body: {reviewer: review.reviewer, grade: review.grade, justification: review.justification}
            })
                .then((response: Review) => dispatch({
                    type: ADD_REVIEW,
                    payload: {proposalId: proposalId, review: response}
                }))
                .catch(logRequestError)
        ,

        updateReview: (conferenceId: number, proposalId: number, review: Review) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "PUT",
                url: `${domain}/api/conferences/${conferenceId}/proposals/${proposalId}/reviews`,
                json: true,
                headers: buildAuthHeader(getState()),
                body: {reviewer: review.reviewer, grade: review.grade, justification: review.justification}
            })
                .then(_ => dispatch({
                    type: UPDATE_REVIEW,
                    payload: {proposalId: proposalId, review: review}
                }))
                .catch(logRequestError)
        ,

        getReviews: (conferenceId: number, proposalId: number) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "GET",
                headers: buildAuthHeader(getState()),
                url: `${domain}/api/conferences/${conferenceId}/proposals/${proposalId}/reviews`
            })
                .then((response: Review[]) => dispatch({
                    type: FETCH_REVIEWS,
                    payload: {reviews: response}
                }))
                .catch(logRequestError)
        ,

        bid: (conferenceId: number, proposalId: number, email: string) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "PUT",
                url: `${domain}/api/conferences/${conferenceId}/proposals/${proposalId}/bid`,
                headers: buildAuthHeader(getState()),
                json: true,
                body: {email: email}
            })
                .then(_ => dispatch({
                    type: ADD_BID,
                    payload: {proposalId: proposalId, bidder: email}
                }))
                .catch(logRequestError)
        ,

        unbid: (conferenceId: number, proposalId: number, email: string) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: "PUT",
                url: `${domain}/api/conferences/${conferenceId}/proposals/${proposalId}/unbid`,
                headers: buildAuthHeader(getState()),
                json: true,
                body: {email: email}
            })
                .then(_ => dispatch({
                    type: REMOVE_BID,
                    payload: {proposalId: proposalId, bidder: email}
                }))
                .catch(logRequestError)
        ,

        addSecondHandReviewer: (conferenceId: number, proposalId: number, shEmail: string) =>
            (dispatch: Dispatch, getState: RootStateGetter) => request({
                method: 'PUT',
                url: `${domain}/api/conferences/${conferenceId}/proposals/${proposalId}/sh`,
                headers: buildAuthHeader(getState()),
                json: true,
                body: {email: shEmail}
            })
                .then(_ => dispatch({
                    type: ADD_SH,
                    payload: {proposalId: proposalId, sh: shEmail}
                }))
                .catch(logRequestError)
    };

export default proposalService;
