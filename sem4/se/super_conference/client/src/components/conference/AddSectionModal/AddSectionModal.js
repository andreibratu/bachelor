import React, {useEffect, useRef, useState} from 'react';
import './AddSectionModal.css';
import {useDispatch, useSelector} from "react-redux";
import {Modal, ModalBody, ModalButton, ModalFooter, ModalHeader, ROLE} from "baseui/modal";
import {KIND} from "baseui/button";
import {Input, SIZE} from "baseui/input";
import {Datepicker} from "baseui/datepicker";
import {FormControl} from "baseui/form-control";
import {Textarea} from "baseui/textarea";
import {Select} from "baseui/select";

const AddSectionModal = (props) => {
    const dispatch = useDispatch();
    const {modalOpen, setModalOpen} = props;
    const currEmail = useSelector(state => state.auth.email);
    const ctxConference = useSelector(state => state.context.currentConference);
    const users = useSelector(state => state.user.users.filter(u => u.email !== currEmail));
    const proposals = ctxConference?.proposals;


    const [formValid, setFormValid] = React.useState(true);
    const [sectionName, setSectionName] = React.useState('');
    const [sectionTopics, setSectionTopics] = React.useState('');
    const [sectionProposals, setSectionProposals] = React.useState([]);
    const [sectionChair, setSectionChair] = React.useState(null);
    const [sectionRoom, setSectionRoom] = React.useState(-1);


    const toName = (user) => `${user.firstname} ${user.lastname}`;
    let userOptions = users.map(u => ({label: toName(u), id: u.email}));

    useEffect(() => {
        setFormValid([
            sectionName !== '',
            sectionTopics !== '',
            sectionProposals?.length > 0,
            sectionChair != null,
            sectionRoom > 0]
            .every(v => v))
    }, [sectionName, sectionTopics, sectionProposals, sectionChair, sectionRoom]);

    return (
        <div className="AddSectionModal">
            <Modal
                onClose={() => setModalOpen(false)}
                closeable
                isOpen={modalOpen}
                animate
                autoFocus
                size={SIZE.default}
                role={ROLE.default}
            >
                <ModalHeader>Add Sections</ModalHeader>
                <ModalBody>
                    <FormControl label={() => "Section Name"}>
                        <Input
                            value={sectionName}
                            onChange={e => setSectionName(e.target.value)}
                            placeholder="Input section name"
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Section Topics"}>
                        <Input
                            value={sectionTopics}
                            onChange={e => setSectionTopics(e.target.value)}
                            placeholder="Input section topics"
                            size={SIZE.compact}/>
                    </FormControl>

                    <FormControl label={() => "Section Proposals"}>
                        <Select
                            size={SIZE.compact}
                            options={proposals}
                            value={sectionProposals}
                            placeholder="Select Section Proposals"
                            onChange={params => setSectionProposals(params.value)}
                            multi
                            closeOnSelect={false}/>
                    </FormControl>

                    <FormControl label={() => "Section Chair"}>
                        <Select
                            size={SIZE.compact}
                            options={userOptions}
                            value={sectionChair}
                            placeholder="Select Section Chair"
                            onChange={params => {
                                console.log(params.value);
                                setSectionChair(params.value);
                            }}
                            multi
                            closeOnSelect={false}
                        />
                    </FormControl>

                    <FormControl label={() => "Section Room Number"}>
                        <Input
                            value={sectionRoom}
                            onChange={e => setSectionRoom(e.target.value.number)}
                            placeholder="Input Room Number"
                            size={SIZE.compact}/>
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

AddSectionModal.propTypes = {};

AddSectionModal.defaultProps = {};

export default AddSectionModal;
