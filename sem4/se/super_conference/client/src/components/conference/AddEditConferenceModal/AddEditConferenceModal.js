import React, {useEffect, useRef} from 'react';
import PropTypes from 'prop-types';
import './AddEditConferenceModal.css';
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader, ROLE} from "baseui/modal";
import {KIND} from "baseui/button";
import {Input, SIZE} from "baseui/input";
import {Datepicker} from "baseui/datepicker";
import {FormControl} from "baseui/form-control";
import {Textarea} from "baseui/textarea";
import {Select} from "baseui/select";
import {useDispatch, useSelector} from "react-redux";

const AddEditConferenceModal = (props) => {
    const {modalOpen, setModalOpen} = props;
    const dispatch = useDispatch();
    const currEmail = useSelector(state => state.auth.email);
    const ctxConference = useSelector(state => state.context.currentConference);
    const users = useSelector(state => state.user.users.filter(u => u.email !== currEmail));

    const [formValid, setFormValid] = React.useState(true);
    const [conferenceTitle, setConferenceTitle] = React.useState('');
    const [conferenceDescription, setConferenceDescription] = React.useState('');
    const [zeroDeadline, setZeroDeadline] = React.useState(null);
    const [abstractDeadline, setAbstractDeadline] = React.useState(null);
    const [proposalDeadline, setProposalDeadline] = React.useState(null);
    const [biddingDeadline, setBiddingDeadline] = React.useState(null);
    const [evaluationDeadline, setEvaluationDeadline] = React.useState(null);
    const [presentationDeadline, setPresentationDeadline] = React.useState(null);
    const [scmUsers, setScmUsers] = React.useState([]);
    const [cpcmUser, setCpcmUser] = React.useState([]);
    const [pcmUsers, setPcmUsers] = React.useState([]);

    let stateReceived = useRef(false);

    const toName = (user) => `${user.firstname} ${user.lastname}`;

    useEffect(() => {
        if (!stateReceived.current && ctxConference != null) {
            setConferenceTitle(ctxConference.title);
            setConferenceDescription(ctxConference.description);
            setZeroDeadline(ctxConference.zeroDeadline);
            setAbstractDeadline(ctxConference.abstractDeadline);
            setProposalDeadline(ctxConference.proposalDeadline);
            setBiddingDeadline(ctxConference.biddingDeadline);
            setEvaluationDeadline(ctxConference.evaluationDeadline);
            setPresentationDeadline(ctxConference.presentationDeadline);
            setScmUsers(ctxConference.scms?.map(u => ({label: toName(u), id: u.email})));
            setCpcmUser([ctxConference.cpcm]?.map(u => ({label: toName(u), id: u.email})));
            setPcmUsers(ctxConference.pcms?.map(u => ({label: toName(u), id: u.email})));
            stateReceived.current = true;
        }
    }, [ctxConference]);

    let userOptions = users.map(u => ({label: toName(u), id: u.email}));

    useEffect(() => {
        setFormValid([
            conferenceTitle !== '',
            conferenceDescription !== '',
            zeroDeadline != null,
            abstractDeadline != null && abstractDeadline > zeroDeadline,
            ((abstractDeadline == null && proposalDeadline > zeroDeadline) ||
                (abstractDeadline != null && proposalDeadline > abstractDeadline)),
            biddingDeadline != null && biddingDeadline > proposalDeadline,
            evaluationDeadline != null && evaluationDeadline > biddingDeadline,
            presentationDeadline != null && presentationDeadline > evaluationDeadline,
            scmUsers?.length > 0,
            cpcmUser != null,
            pcmUsers?.length > 2]
            .every(v => v))
    }, [
        conferenceTitle, conferenceDescription, zeroDeadline, abstractDeadline, biddingDeadline, evaluationDeadline,
        presentationDeadline, scmUsers, cpcmUser, pcmUsers, proposalDeadline]);

    return (
        <div className="ConferenceModal" data-testid="AddEditConferenceModal">
            <Modal
                onClose={() => setModalOpen(false)}
                closeable
                isOpen={modalOpen}
                animate
                autoFocus
                size={SIZE.default}
                role={ROLE.default}
            >
                <ModalHeader>Add Conference</ModalHeader>
                <ModalBody>
                    <FormControl label={() => "Conference Name"}>
                        <Input
                            value={conferenceTitle}
                            onChange={e => setConferenceTitle(e.target.value)}
                            placeholder="Input conference name"
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Conference Description"}>
                        <Textarea
                            value={conferenceDescription}
                            onChange={e => setConferenceDescription(e.target.value)}
                            placeholder="Input conference description"
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Zero Deadline"}>
                        <Datepicker
                            value={zeroDeadline}
                            onChange={({date}) => setZeroDeadline(date)}
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl
                        label={() => "Submit Abstract Deadline"}
                        caption={() => "Leave blank if only integral Proposals are accepted."}
                    >
                        <Datepicker
                            value={abstractDeadline}
                            onChange={({date}) => setAbstractDeadline(date)}
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Submit Proposal Deadline"}>
                        <Datepicker
                            value={proposalDeadline}
                            onChange={({date}) => setProposalDeadline(date)}
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Bidding Deadline"}>
                        <Datepicker
                            value={biddingDeadline}
                            onChange={({ date }) => setBiddingDeadline(date)}
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Evaluation Deadline"}>
                        <Datepicker
                            value={evaluationDeadline}
                            onChange={({date}) => setEvaluationDeadline(date)}
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Presentation Deadline"}>
                        <Datepicker
                            value={presentationDeadline}
                            onChange={({ date }) => setPresentationDeadline(date)}
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "SCM Members"}>
                        <Select
                            size={SIZE.compact}
                            options={userOptions}
                            value={scmUsers}
                            placeholder="Select SCM members"
                            onChange={params => setScmUsers(params.value)}
                            multi
                            closeOnSelect={false}/>
                    </FormControl>

                    <FormControl label={() => "PCM Members"}>
                        <Select
                            size={SIZE.compact}
                            options={userOptions}
                            value={pcmUsers}
                            placeholder="Select PCM members"
                            onChange={params => {
                                console.log(params.value);
                                setPcmUsers(params.value);
                            }}
                            multi
                            closeOnSelect={false}
                        />
                    </FormControl>

                    <FormControl label={() => "Chair PCM"}>
                        <Select
                            size={SIZE.compact}
                            options={userOptions}
                            value={pcmUsers}
                            placeholder="Select Chair for PC"
                            onChange={params => {
                                console.log(params.value);
                                setCpcmUser(params.value);
                            }}
                        />
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
    )
};

AddEditConferenceModal.propTypes = {
    modalOpen: PropTypes.bool.isRequired,
    setModalOpen: PropTypes.func.isRequired,
};

AddEditConferenceModal.defaultProps = {
};

export default AddEditConferenceModal;
