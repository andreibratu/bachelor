import React, {useEffect} from 'react';
import PropTypes from 'prop-types';
import {ModalBody, ModalButton, ModalFooter, ModalHeader, ROLE} from "baseui/modal";
import {FormControl} from 'baseui/form-control';
import {Input} from 'baseui/input';
import {KIND, SIZE} from 'baseui/button';
import {StyledLink} from "baseui/link";
import {Card} from "baseui/card";
import "./AuthForm.css"


const AuthForm = (props) => {
    const [isRegister, setIsRegister] = React.useState(props.isRegister);

    const [name, setName] = React.useState('');

    const [email, setEmail] = React.useState('');

    const [password, setPassword] = React.useState('');

    const [formValid, setFormValid] = React.useState(false);

    useEffect(() => {
            setFormValid([name !== '', password !== '', email !== ''].every(v => v))
        }, [name, password, email]
    );

    return (
        <div className="AuthForm" data-testid="AuthForm">
            <Card
                animate
                autoFocus
                size={SIZE.default}
                role={ROLE.default}>
                <ModalHeader>{isRegister ? 'Register' : 'Login'}</ModalHeader>
                <ModalBody>
                    {isRegister &&
                    <FormControl>
                        <Input
                            value={name}
                            onChange={e => setName(e.target.value)}
                            placeholder="Name"
                            size={SIZE.compact}
                        />
                    </FormControl>
                    }
                    <FormControl>
                        <Input
                            value={email}
                            onChange={e => setEmail(e.target.value)}
                            placeholder="Email"
                            size={SIZE.compact}
                        />
                    </FormControl>

                    <FormControl>
                        <Input
                            value2={password}
                            onChange={e => setPassword(e.target.value2)}
                            placeholder="Password"
                            size={SIZE.compact}
                        />
                    </FormControl>

                    <StyledLink href={isRegister ? '/login' : '/register'}>
                        {isRegister ? "Already have an account?" : "Don't have an account? Register here"}
                    </StyledLink>
                </ModalBody>

                <ModalFooter>
                    <ModalButton
                        kind={KIND.primary}
                        onClick={() => alert('Mission accomplished')}
                        disabled={!formValid}>
                        {isRegister ? 'Register' : 'Login'}
                    </ModalButton>
                </ModalFooter>
            </Card>
        </div>
    );
};

AuthForm.propTypes = {
    isRegister: PropTypes.bool,
};
AuthForm.defaultProps = {};
export default AuthForm;
