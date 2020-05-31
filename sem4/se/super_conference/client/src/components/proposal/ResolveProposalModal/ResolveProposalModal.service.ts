import {Conference, Email, Proposal, Review, User} from "../../../redux/entities";

export function getSecondHandReview(
    secondHandReviewer: Email,
    proposalId: number,
    reviews: Review[]
) {
    let secondHandReviewId = reviews?.findIndex(r =>
        r.reviewer === secondHandReviewer &&
        r.proposalId === proposalId
    );
    let secondHandReview;
    if (secondHandReviewId === -1) {
        secondHandReview = null;
    } else {
        secondHandReview = reviews?.find(r => r.id === secondHandReviewId);
        reviews = reviews?.filter(r => r.id !== secondHandReviewId);
    }
    return [secondHandReview, reviews];
}

export function getPCMsAvailableSecondHand(
    conference: Conference,
    proposal: Proposal,
    firstHandReviews: Review[]
) {
    if (firstHandReviews == null) return null;

    const firstHandReviewers = firstHandReviews.map(r => r.reviewer);
    const authors = proposal?.coAuthors.concat(proposal.author);
    const illegal = authors?.concat(conference?.cpcm);
    // @ts-ignore
    return conference?.pcms.filter(pcm =>
        !firstHandReviewers.includes(pcm) &&
        !illegal.includes(pcm)
    );
}

export function buildSecondHandSelectOptions(
    users: User[],
    availablePCMs: Email[]
): { label: string, id: string }[] {
    let pcmProfiles = users.filter(u => availablePCMs?.includes(u.email));
    return pcmProfiles.map(u => ({label: `${u.firstname} ${u.lastname}`, id: u.email}));
}
