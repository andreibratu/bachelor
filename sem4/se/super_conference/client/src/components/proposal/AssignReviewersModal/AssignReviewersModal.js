import React, {useEffect, useRef, useState} from 'react';
import './AssignReviewersModal.css';
import PropTypes from 'prop-types';
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader, ROLE} from "baseui/modal";
import {SIZE} from "baseui/input";
import {KIND} from "baseui/button";
import {FormControl} from "baseui/form-control";
import {Select} from "baseui/select";

import {useDispatch, useSelector} from "react-redux";

const AssignReviewersModal = (props) => {
    const dispatch = useDispatch();
    const {modalOpen, setModalOpen} = props;
    const currentEmail = useSelector(state => state.auth.email);
    const currentProposal = useSelector(state => state.context.currentProposal);
    const users = useSelector(state => state.user.users.filter(u => u.email !== currentEmail));//.filter(u => u.email in currentProposal.bidders));

    const [formValid, setFormValid] = React.useState(true);
    const [proposalReviewers, setProposalReviewers] = React.useState([]);

    const toName = (user) => `${user.firstname} ${user.lastname}`;
    let stateReceived = useRef(false);

    useEffect( () => {
        if (!stateReceived.current && currentProposal != null) {
            setProposalReviewers(currentProposal.reviewers?.map(u => ({label: toName(u), id: u.email})));
        }
    }, [currentProposal]);

    let userOptions = users.map(u => ({label: toName(u), id: u.email}));

    useEffect(() => {
        setFormValid([
            proposalReviewers?.length > 2,
            proposalReviewers?.length < 5]
            .every(v => v))
    }, [proposalReviewers]);


    return (
        <div className="AssignReviewersModal">
            <Modal
                onClose={() => setModalOpen(false)}
                closeable
                isOpen={modalOpen}
                animate
                autoFocus
                size={SIZE.default}
                role={ROLE.default}
            >
                <ModalHeader>Assign Reviewers</ModalHeader>
                <ModalBody>

                    <FormControl label={() => "Reviewers"}>
                        <Select
                            size={SIZE.compact}
                            options={userOptions}
                            value={proposalReviewers}
                            placeholder="Select Reviewers"
                            onChange={params => setProposalReviewers(params.value)}
                            multi
                            closeOnSelect={false}/>
                    </FormControl>
                </ModalBody>

                <ModalFooter>
                    <ModalButton
                        kind={KIND.secondary}
                        onClick={() => setModalOpen(false)}
                        size={SIZE.compact}>
                        Cancel
                    </ModalButton>
                    <ModalButton
                        size={SIZE.compact}
                        disabled={!formValid}
                        onClick={() => alert('Much action, wow..')}>
                        Submit
                    </ModalButton>
                </ModalFooter>
            </Modal>
        </div>
    );
};

AssignReviewersModal.propTypes = {};

AssignReviewersModal.defaultProps = {};

export default AssignReviewersModal;