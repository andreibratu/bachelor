import React, {useState} from 'react';
import './ResolveProposalModal.css';
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader, ROLE, SIZE} from "baseui/modal";
import {Button, KIND} from "baseui/button";
import {useDispatch, useSelector} from "react-redux";
import EvaluationCard from "../EvaluationCard/EvaluationCard";
import {Heading, HeadingLevel} from "baseui/heading";
import {
    buildSecondHandSelectOptions,
    getPCMsAvailableSecondHand,
    getSecondHandReview
} from "./ResolveProposalModal.service";
import {Select} from "baseui/select";

const ResolveProposalModal = (props) => {
    const {modalOpen, setModalOpen} = props;

    const [selectedSHReviewer, setSelectedSHReviewer] = useState(null);

    const dispatch = useDispatch();
    const cProposal = useSelector(state => state.context.currentProposal);
    const users = useSelector(state => state.user.users);
    let allReviews = useSelector(state => state.proposal.reviews);
    const conference = useSelector(
        state => state.conference.conferences.find(c => c.id === cProposal?.conferenceId)
    );

    let [secondHandReview, firstHandReviews] = getSecondHandReview(
        cProposal?.secondHandReviewer,
        cProposal?.id,
        allReviews
    );

    let pcmEmails = secondHandReview !== -1 ?
        getPCMsAvailableSecondHand(conference, cProposal, firstHandReviews)
        :
        null;
    let pcmProfiles = buildSecondHandSelectOptions(users, pcmEmails);

    console.log('PROFILES', pcmProfiles);

    return (
        <div className="ResolveProposalModal" data-testid="ResolveProposalModal">
            <Modal
                onClose={() => setModalOpen(false)}
                closeable
                isOpen={modalOpen}
                animate
                autoFocus
                size={SIZE.default}
                role={ROLE.default}>
                <ModalHeader>{cProposal?.proposalName}</ModalHeader>
                <ModalBody>
                    <HeadingLevel>
                        <Heading styleLevel={6}>Reviews</Heading>
                        {
                            firstHandReviews?.map(review => <EvaluationCard key={review.id} {...review} />)
                        }
                        <Heading styleLevel={6}>Second Hand Reviewer</Heading>
                        {
                            cProposal?.secondHandReviewer != null ?
                                (
                                    (
                                        secondHandReview &&
                                        <EvaluationCard key={secondHandReview.id} {...secondHandReview}/>
                                    )
                                    ||
                                    (<p>The second hand reviewer has not evaluated the proposal yet</p>)
                                )
                                :
                                (
                                    pcmProfiles.length !== 0 ?
                                        (
                                            <div className={'secondHandDiv'}>
                                                <Select
                                                    options={pcmProfiles}
                                                    size={SIZE.compact}
                                                    clearable={false}
                                                    value=
                                                        {
                                                            selectedSHReviewer != null ?
                                                                [pcmProfiles.find(p => p.id === selectedSHReviewer)]
                                                                :
                                                                []
                                                        }
                                                    onChange={params => {
                                                        console.log(params);
                                                        setSelectedSHReviewer(params.value[0].id);
                                                        console.log(selectedSHReviewer);
                                                    }}
                                                    escapeClearsValue={false}
                                                    searchable={false}
                                                    placeholder={'Select...'}
                                                />
                                                <Button
                                                    kind={KIND.primary}
                                                    size={SIZE.compact}
                                                    onClick={() => {

                                                    }}>
                                                    Select
                                                </Button>
                                            </div>
                                        )
                                        :
                                        (<p>No PCMs qualify for Second Hand Reviewer position!</p>)
                                )
                        }
                    </HeadingLevel>
                </ModalBody>
                <ModalFooter>
                    <ModalButton
                        kind={KIND.secondary}
                        onClick={() => setModalOpen(false)}
                        size={SIZE.default}>
                        Cancel
                    </ModalButton>
                    <ModalButton
                        kind={KIND.negative}
                        size={SIZE.compact}
                        onClick={() => setModalOpen(false)}
                        overrides={{
                            BaseButton: {style: ({$theme}) => ({backgroundColor: $theme.colors.negative400})}
                        }}>
                        Reject
                    </ModalButton>
                    <ModalButton
                        kind={KIND.positive}
                        onClick={() => setModalOpen(false)}
                        size={SIZE.default}
                        overrides={{
                            BaseButton: {style: ({$theme}) => ({backgroundColor: $theme.colors.positive400})}
                        }}>
                        Approve
                    </ModalButton>
                </ModalFooter>
            </Modal>
        </div>
    );
};

export default ResolveProposalModal;
