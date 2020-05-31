import React, {useEffect, useRef, useState} from 'react';
import './AddEditProposalModal.css';
import {FormControl} from "baseui/form-control";
import {Input, SIZE as INPUT_SIZE} from "baseui/input";
import {Textarea} from "baseui/textarea";
import TagInput from "../../generic/TagInput/TagInput";
import {KIND as TAG_KIND} from "baseui/tag";
import {KIND as BUTTON_KIND} from 'baseui/button';
import {FileUploader} from "baseui/file-uploader";
import {Select} from "baseui/select";
import {useDispatch, useSelector} from "react-redux";
import {FILE_SUBMITTED_TOKEN} from '../../../constants'
import {
    Modal,
    ModalBody,
    ModalButton,
    ModalFooter,
    ModalHeader,
    ROLE as MODAL_ROLE,
    SIZE as MODAL_SIZE
} from "baseui/modal";
import proposalService from "../../../redux/proposal/proposalService";
import {Heading, HeadingLevel} from "baseui/heading";
import EvaluationCard from "../EvaluationCard/EvaluationCard";

const AddEditProposalModal = (props) => {
    const dispatch = useDispatch();
    const {modalOpen, setModalOpen, improveScenario} = props;

    // Context
    const contextProposal = useSelector(state => state.context.currentProposal);
    const currUserEmail = useSelector(state => state.auth.email);

    // Entities
    const conferences = useSelector(
        state => state.conference.conferences.map(c => c.proposalDeadline > Date.now())
    );
    const users = useSelector(
        state => state.user.users.filter(u => u.email !== currUserEmail)
    );
    const proposalReviews = useSelector(
        state => state.proposal.reviews.filter(r => r.proposalId === contextProposal?.id)
    );
    let editScenario = contextProposal != null;

    // Entity fields
    const [proposalName, setProposalName] = useState('');
    const [abstract, setAbstract] = useState('');
    const [topics, setTopics] = useState([]);
    const [keywords, setKeywords] = useState([]);
    const [proposalFile, setProposalFile] = useState(
        contextProposal?.filePath ? FILE_SUBMITTED_TOKEN : null
    );
    const [coAuthors, setCoAuthors] = useState([]);

    let stateReceived = useRef(false);

    useEffect(() => {
        if (!stateReceived.current && contextProposal != null) {
            setProposalName(contextProposal.proposalName);
            setAbstract(contextProposal.abstract);
            setTopics(contextProposal.topics);
            setKeywords(contextProposal.keywords);
            setCoAuthors(contextProposal.coAuthors);
            setFormValid(true);
            stateReceived.current = true;
        }
    }, [contextProposal]);

    // Form logic
    const [selectedOption, setSelectedOption] = useState(null);
    const [formValid, setFormValid] = useState(true);
    const [progressMessage, setProgressMessage] = useState('');
    const [progressAmount, setProgressAmount] = useState(null);
    const [conferenceId, setConferenceId] = useState(
        contextProposal ? contextProposal.conferenceId : null
    );
    const [fileInputCaption, setFileInputCaption] = useState('');

    // Options for select
    let conferenceOptions = conferences.map(c => ({label: c.title, id: c.id}));
    let coAuthorsOptions = users.map(u => ({label: `${u.firstname} ${u.lastname}`, id: u.email}));

    useEffect(() => {
        let dependencies;
        if (conferenceId?.abstractDeadline) {
            dependencies = [proposalName, abstract, topics, keywords];
            setFileInputCaption(
                `Proposal can be uploaded at a later time. Deadline: ${conferenceId?.abstractDeadline}`
            );
        } else {
            dependencies = [proposalName, abstract, topics, keywords, proposalFile];
            setFileInputCaption('Proposal upload is mandatory.')
        }
        setFormValid(dependencies.every(e => e != null && e !== ''));
    }, [conferenceId, proposalFile, proposalName, abstract, topics, keywords, selectedOption]);

    const scenario = editScenario ? (improveScenario ? 'Improve' : 'Edit') : 'Submit';

    return (
        <div className="AddProposal">
            <Modal
                onClose={() => setModalOpen(false)}
                isOpen={modalOpen}
                animate
                autoFocus
                size={MODAL_SIZE.default}
                role={MODAL_ROLE.default}
            >
                {!improveScenario && <ModalHeader>{`${scenario} Proposal`}</ModalHeader>}
                <ModalBody>
                    {
                        improveScenario &&
                        <HeadingLevel>
                            <Heading styleLevel={6}>Reviews</Heading>
                            {
                                proposalReviews.map(r =>
                                    <EvaluationCard key={r.id} {...r}/>
                                )
                            }
                            <Heading styleLevel={6}>Improve Proposal</Heading>
                        </HeadingLevel>
                    }

                    <div className={'AddProposalFormDiv'}>
                        {
                            !improveScenario &&
                            <FormControl label={'Proposal Title'}>
                                <Input
                                    size={INPUT_SIZE.compact}
                                    placeholder={'Enter your proposal title'}
                                    onChange={value => setProposalName(value)}
                                />
                            </FormControl>
                        }

                        {
                            !improveScenario && !editScenario &&
                            <FormControl label={'Conference'}>
                                <Select
                                    clearable={false}
                                    deleteRemoves={false}
                                    escapeClearsValue={false}
                                    searchable={false}
                                    size={INPUT_SIZE.compact}
                                    options={conferenceOptions}
                                    value={selectedOption ? [selectedOption] : null}
                                    onChange={e => {
                                        setSelectedOption(e.value[0]);
                                        setConferenceId(e.value[0].id);
                                    }}/>
                            </FormControl>
                        }

                        {
                            <FormControl label={'Abstract'}>
                                <Textarea
                                    placeholder={'Enter a brief description of the proposal'}
                                    size={INPUT_SIZE.compact}
                                    value={abstract}
                                    onChange={e => setAbstract(e.target.value)}
                                />
                            </FormControl>
                        }

                        {
                            !improveScenario &&
                            <FormControl
                                label={'Topics'}
                                caption={'Topics can be separated by Enter or Space'}>
                                <TagInput
                                    size={INPUT_SIZE.compact}
                                    tagKind={TAG_KIND.accent}
                                    controlCallback={setTopics}
                                    controlValue={topics}
                                    placeholder={'Enter topics or areas touched by your proposal'}
                                />
                            </FormControl>
                        }

                        {
                            !improveScenario &&
                            <FormControl
                                label={'Keywords'}
                                caption={'Keywords can be separated by Enter or Space'}
                            >
                                <TagInput
                                    size={INPUT_SIZE.compact}
                                    tagKind={TAG_KIND.neutral}
                                    controlCallback={setKeywords}
                                    controlValue={keywords}
                                    placeholder={'Enter keywords that summarize your proposal'}
                                />
                            </FormControl>
                        }

                        {
                            !improveScenario &&
                            <FormControl label={'Co-Authors'}>
                                <Select
                                    size={INPUT_SIZE.compact}
                                    clearable={false}
                                    closeOnSelect={false}
                                    deleteRemoves={false}
                                    escapeClearsValue={false}
                                    options={coAuthorsOptions}
                                    value={coAuthors}
                                    filterOutSelected={false}
                                    multi
                                    searchable={false}
                                    placeholder="Add Co-Authors"
                                    onChange={params => setCoAuthors(params.value)}
                                />
                            </FormControl>
                        }

                        {
                            <FormControl
                                label={'Proposal'}
                                caption={(proposalFile === FILE_SUBMITTED_TOKEN || improveScenario) ?
                                    'Your last submission has been registered'
                                    :
                                    fileInputCaption
                                }>
                                <FileUploader
                                    onCancel={() => {
                                        setProgressAmount(null);
                                        setProgressMessage(null);
                                    }}
                                    onDrop={accepted => {
                                        let reader = new FileReader();
                                        reader.onload = () => {
                                            setProposalFile(reader.result.slice(37));
                                        };
                                        reader.readAsDataURL(accepted[0]);
                                        setProgressAmount(100);
                                        setProgressMessage('Your proposal has been registered!')
                                    }}
                                    progressAmount={progressAmount}
                                    progressMessage={progressMessage}
                                />
                            </FormControl>
                        }

                        <ModalFooter>
                            <ModalButton
                                kind={BUTTON_KIND.secondary}
                                onClick={() => {
                                    setProposalName('');
                                    setAbstract('');
                                    setCoAuthors([]);
                                    setKeywords([]);
                                    setTopics([]);
                                    props.setModalOpen(false);
                                }}
                                size={INPUT_SIZE.compact}>
                                Cancel
                            </ModalButton>
                            <ModalButton
                                size={INPUT_SIZE.compact}
                                disabled={!formValid}
                                onClick={() => {
                                    if (editScenario) {
                                        dispatch(proposalService.updateProposal(
                                            conferenceId,
                                            {
                                                id: contextProposal.id,
                                                author: currUserEmail,
                                                proposalName: proposalName,
                                                abstract: abstract,
                                                keywords: keywords,
                                                coAuthors: coAuthors.map(opt => opt.id),
                                                bidders: contextProposal.bidders,
                                                reviewers: contextProposal.reviewers,
                                                secondHandReviewer: contextProposal.secondHandReviewer,
                                            },
                                            proposalFile === FILE_SUBMITTED_TOKEN ? null : proposalFile
                                        ))
                                    } else {
                                        dispatch(proposalService.addProposal(
                                            conferenceId,
                                            {
                                                author: currUserEmail,
                                                proposalName: proposalName,
                                                topics: topics,
                                                conferenceId: conferenceId,
                                                keywords: keywords,
                                                // Select email
                                                coAuthors: coAuthors.map(opt => opt.id),
                                            },
                                            proposalFile
                                        ));
                                    }
                                }}>
                                {editScenario ? 'Update' : 'Submit'}
                            </ModalButton>
                        </ModalFooter>
                    </div>
                </ModalBody>
            </Modal>
        </div>
    );
};

AddEditProposalModal.propTypes = {};

AddEditProposalModal.defaultProps = {};

export default AddEditProposalModal;
