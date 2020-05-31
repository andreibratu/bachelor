import React, {useEffect, useState} from 'react';
import './AttendConferenceModal.css';
import {useDispatch, useSelector} from "react-redux";
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader} from "baseui/modal";
import conferenceService from "../../../redux/conference/conferenceService";

const AttendConferenceModal = (props) => {
    const dispatch = useDispatch();
    const currentEmail = useSelector(state => state.auth.email);
    const currentConference = useSelector(state => state.context.currentConference);
    const {modalOpen, setModalOpen} = props;
    const close = () => setModalOpen(false);
    const [hasAttended, setHasAttended] = useState(false);

    useEffect(() =>
            setHasAttended(currentConference?.participants.includes(currentEmail)),
        [currentConference, currentEmail]
    );

    const attend = () => {
        dispatch(conferenceService.addParticipantToConference(
            currentEmail,
            currentConference.conferenceId
        ));
        close();
    };

    const unAttend = () => {
        dispatch(conferenceService.removeParticipantFromConference(
            currentEmail,
            currentConference.conferenceId
        ));
        close();
    };

    return (
        <div className="AttendConferenceModal">
            <Modal onClose={close} isOpen={modalOpen}>
                <ModalHeader>Confirm</ModalHeader>
                <ModalBody>
                    {
                        hasAttended ?
                            'Are you sure you want to cancel your attendance?'
                            :
                            'Are you sure you want to attend for this conference?'
                    }
                </ModalBody>
                <ModalFooter>
                    <ModalButton kind="tertiary" onClick={close}>Cancel</ModalButton>
                    <ModalButton onClick={hasAttended ? attend : unAttend}>Okay</ModalButton>
                </ModalFooter>
            </Modal>
        </div>
    );
};

AttendConferenceModal.propTypes = {};

AttendConferenceModal.defaultProps = {};

export default AttendConferenceModal;
