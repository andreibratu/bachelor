import React, {useEffect, useRef} from 'react';
import './ReviewProposalModal.css';
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader, ROLE, SIZE} from "baseui/modal";
import {FormControl} from "baseui/form-control";
import {Textarea} from "baseui/textarea";
import {KIND} from "baseui/button";
import {Select} from "baseui/select";
import {useDispatch, useSelector} from "react-redux";
import proposalService from "../../../redux/proposal/proposalService";

const ReviewProposalModal = (props) => {
    /**
     * props.review object will only be present if this is an edit of a former Review
     * props.review.grade is expected as an object with properties `label` and `id` per the Select item below.
     * props.review.justification has a string value
     */
    const {modalOpen, setModalOpen} = props;

    const dispatch = useDispatch();
    const proposal = useSelector(state => state.context.currentProposal);
    const review = useSelector(state => state.context.currentReview);
    const currentUserEmail = useSelector(state => state.auth.email);

    let stateReceived = useRef(false);

    const options = [
        {label: "Strong Reject (-3)", id: -3},
        {label: "Reject (-2)", id: -2},
        {label: "Weak Reject (-1)", id: -1},
        {label: "Borderline (0)", id: 0},
        {label: "Weak Accept (1)", id: 1},
        {label: "Accept (2)", id: 2},
        {label: "Strong Accept (3)", id: 3}
    ];

    let [formValid, setFormValid] = React.useState(review != null);

    let [grade, setGrade] = React.useState(review != null ? review.grade : null);
    let [gradeValid, setGradeValid] = React.useState(review != null);

    let [justification, setJustification] = React.useState(review !== null ? review.justification : '');
    let [justificationValid, setJustificationValid] = React.useState(review != null);

    useEffect(() => {
        if (!stateReceived.current && review != null) {
            setGrade(review.grade);
            setJustification(review.justification);
            stateReceived.current = true;
        }
    }, [review, options]);

    useEffect(() => {
        setGradeValid(grade != null);
        setJustificationValid(justification !== '');
        setFormValid([gradeValid, justificationValid].every(v => v))
    }, [gradeValid, justificationValid, grade, justification]);

    return (
        <div className="ReviewProposalModal" data-testid="ReviewProposalModal">
            <Modal
                onClose={() => setModalOpen(false)}
                closeable
                isOpen={modalOpen}
                animate
                autoFocus
                size={SIZE.default}
                role={ROLE.default}
            >
                <ModalHeader>{proposal != null ? proposal.proposalName : ''}</ModalHeader>
                <ModalBody>
                    <FormControl label={() => "Grade"}>
                        <Select
                            backspaceRemoves={false}
                            clearable={false}
                            options={options}
                            value={grade != null ? [options.find(o => o.id === grade)] : []}
                            error={!gradeValid}
                            placeholder="Grade the Proposal"
                            onChange={params => setGrade(params.value[0].id)}/>
                    </FormControl>

                    <FormControl label={() => "Justification"}>
                        <Textarea
                            value={review != null ? justification : ''}
                            error={!justificationValid}
                            size={SIZE.default}
                            onChange={(e) => setJustification(e.target.value)}/>
                    </FormControl>

                    <ModalFooter>
                        <ModalButton
                            kind={KIND.secondary}
                            onClick={() => props.setModalOpen(false)}
                            size={SIZE.default}>
                            Cancel
                        </ModalButton>
                        <ModalButton
                            size={SIZE.compact}
                            disabled={!formValid}
                            onClick={() => {
                                if (!review) {
                                    dispatch(proposalService.addReview(
                                        proposal.conferenceId,
                                        proposal.id,
                                        {
                                            proposalId: proposal.id,
                                            reviewer: currentUserEmail,
                                            grade: grade,
                                            justification: justification
                                        }
                                    ))
                                } else {
                                    dispatch(proposalService)
                                }
                            }}>
                            {review != null ? 'Update' : 'Submit'}
                        </ModalButton>
                    </ModalFooter>
                </ModalBody>
            </Modal>
        </div>
    );
};

ReviewProposalModal.propTypes = {};

ReviewProposalModal.defaultProps = {};

export default ReviewProposalModal;
