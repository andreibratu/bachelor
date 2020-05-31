import React, {useEffect, useState} from 'react';
import './BidModal.css';
import {useDispatch, useSelector} from "react-redux";
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader} from "baseui/modal";
import proposalService from "../../../redux/proposal/proposalService";

const BidModal = (props) => {
    const dispatch = useDispatch();
    const currentEmail = useSelector(state => state.auth.email);
    const currentProposal = useSelector(state => state.context.currentProposal);
    const {modalOpen, setModalOpen} = props;
    const close = () => setModalOpen(false);
    const [hasBid, setHasBid] = useState(false);

    useEffect(() =>
            setHasBid(currentProposal?.bidders.includes(currentEmail)),
        [currentProposal, currentEmail]
    );

    const bid = () => {
        dispatch(proposalService.bid(
            currentProposal.conferenceId,
            currentProposal.id,
            currentEmail
        ));
        close();
    };
    const unBid = () => {
        dispatch(proposalService.unbid(
            currentProposal.conferenceId,
            currentProposal.id,
            currentEmail
        ));
        close();
    };

    return (
        <div className="BidModal">
            <Modal onClose={close} isOpen={modalOpen}>
                <ModalHeader>Confirm</ModalHeader>
                <ModalBody>
                    {
                        hasBid ?
                            'Are you sure you want to cancel your bid?'
                            :
                            'Are you sure you want to bid for this proposal?'
                    }
                </ModalBody>
                <ModalFooter>
                    <ModalButton kind="tertiary" onClick={close}>Cancel</ModalButton>
                    <ModalButton onClick={hasBid ? bid : unBid}>Okay</ModalButton>
                </ModalFooter>
            </Modal>
        </div>
    );
};

BidModal.propTypes = {};

BidModal.defaultProps = {};

export default BidModal;
