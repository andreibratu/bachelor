let domain = "domain";

export default domain;

export type Email = string;
export type ID = number;
export type JWT = string;

export type Proposal = {
    id: ID,
    conferenceId: ID,
    proposalName: string,
    filePath: string,
    abstract: string,
    topics: string[],
    keywords: string[],
    author: string,
    coAuthors: Email[],
    bidders: Email[],
    reviewers: Email[],
    secondHandReviewer: Email | null
}

export type User = {
    email: string,
    firstname: string,
    lastname: string,
}

export type Section = {
    id: ID | null,
    name: string,
    topics: string[],
    proposals: ID[] | null,
    chair: Email,
    room: number
}

export type Review = {
    id: ID,
    proposalId: ID,
    reviewer: Email,
    grade: number,
    justification: string
}

export type Conference = {
    id: ID | null,
    title: string,
    description: string,
    zeroDeadline: Date,
    abstractDeadline: Date,
    proposalDeadline: Date,
    biddingDeadline: Date,
    evaluationDeadline: Date,
    presentationDeadline: Date,
    participants: Email[] | null,
    // TODO Might need to add below properties
    scms: Email[],
    cscm: Email,
    pcms: Email[],
    cpcm: Email,
    sections: Section[]
}

export type Notification = {
    id: ID | null,
    text: string,
    href: string
    read: boolean
}

// @ts-ignore
export const buildAuthHeader = (state: object): object => ({Authorization: `Bearer ${state.auth.token}`});
export const logRequestError = (error) => {console.log(error)};
